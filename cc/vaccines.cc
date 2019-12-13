#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>

#include "acmacs-base/filesystem.hh"
#include "acmacs-base/acmacsd.hh"
#include "acmacs-base/settings.hh"
#include "acmacs-chart-2/chart.hh"
#include "acmacs-whocc-data/vaccines.hh"

// see ~/AD/share/conf/vaccines.json

// ----------------------------------------------------------------------

namespace acmacs::whocc::inline v1
{
    class VaccineData : public acmacs::settings::Settings
    {
      public:
        VaccineData()
        {
            using namespace std::string_literals;
            using namespace std::string_view_literals;

            if (const auto filename = fmt::format("{}/share/conf/vaccines.json", acmacs::acmacsd_root()); fs::exists(filename))
                acmacs::settings::Settings::load(filename);
            else
                throw error{fmt::format("WARNING: cannot load \"{}\": file not found\n", filename)};

            using pp = std::pair<std::string, std::string_view>;
            for (const auto& [virus_type, tag] :
                 {pp{"A(H1N1)PDM09"s, "vaccines-A(H1N1)PDM09"sv}, pp{"A(H3N2)"s, "vaccines-A(H3N2)"sv}, pp{"BVICTORIA"s, "vaccines-BVICTORIA"sv}, pp{"BYAMAGATA"s, "vaccines-BYAMAGATA"sv}}) {
                current_virus_type_ = virus_type;
                apply(tag, acmacs::verbose::no);
            }
        }

        bool apply_built_in(std::string_view name, verbose verb) override // returns true if built-in command with that name found and applied
        {
            if (name == "vaccine")
                data_[current_virus_type_].emplace_back(getenv("name", ""), Vaccine::type_from_string(getenv("vaccine_type", "")));
            else
                return acmacs::settings::Settings::apply_built_in(name, verb);
            return true;
        }

        const auto& find(std::string_view virus_type) const
        {
            if (const auto found = data_.find(virus_type); found != data_.end())
                return found->second;
            throw error(fmt::format("No vaccines defined for \"{}\"", virus_type));
        }

      private:
        std::string current_virus_type_;
        std::map<std::string, std::vector<Vaccine>, std::less<>> data_;

    }; // class VaccineData
} // namespace acmacs::whocc::inlinev1

// ----------------------------------------------------------------------

#pragma GCC diagnostic push
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#endif
static std::once_flag sVaccineOnceFlag;
static std::unique_ptr<acmacs::whocc::v1::VaccineData> sVaccines;
#pragma GCC diagnostic pop

const acmacs::whocc::v1::vaccine_names_t& acmacs::whocc::v1::vaccine_names(const acmacs::virus::type_subtype_t& virus_type, const acmacs::virus::lineage_t& lineage)
{
    if (!sVaccines) {
        std::call_once(sVaccineOnceFlag, []() {
            if (!sVaccines)
                sVaccines = std::make_unique<VaccineData>();
        });
    }

    return sVaccines->find(fmt::format("{}{}", virus_type, lineage));

} // acmacs::whocc::v1::vaccine_names

// ----------------------------------------------------------------------

std::string acmacs::whocc::v1::Vaccine::type_as_string(vaccine_type a_type)
{
    switch (a_type) {
      case vaccine_type::previous:
          return "previous";
      case vaccine_type::current:
          return "current";
      case vaccine_type::surrogate:
          return "surrogate";
      case vaccine_type::any:
          return "any";
    }
    return {};

} // acmacs::whocc::v1::Vaccine::type_as_string

// ----------------------------------------------------------------------

acmacs::whocc::v1::vaccine_type acmacs::whocc::v1::Vaccine::type_from_string(std::string_view a_type)
{
    if (a_type == "previous")
        return vaccine_type::previous;
    else if (a_type == "current")
        return vaccine_type::current;
    else if (a_type == "surrogate")
        return vaccine_type::surrogate;
    else if (a_type.empty() || a_type == "any")
        return vaccine_type::any;
    fmt::print(stderr, "WARNING: invalid vaccine type: \"{}|', \"previous\" assumed\n", a_type);
    return vaccine_type::previous;

} // acmacs::whocc::v1::Vaccine::type_from_string

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
