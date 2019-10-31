#pragma once

#include "acmacs-virus/virus-name.hh"

// ----------------------------------------------------------------------

namespace acmacs::whocc::inline v1
{
    enum class vaccine_type { previous, current, surrogate };

    class error : public std::runtime_error { public: using std::runtime_error::runtime_error; };

    class Vaccine
    {
     public:
        Vaccine(std::string_view a_name, vaccine_type a_type) : name{a_name}, type{a_type} {}

        std::string name;
        vaccine_type type;

        std::string type_as_string() const { return type_as_string(type); }

        static std::string type_as_string(vaccine_type a_type);
        static vaccine_type type_from_string(std::string_view a_type);

    }; // class Vaccine

    using vaccine_names_t = std::vector<Vaccine>;

    const vaccine_names_t& vaccine_names(const acmacs::virus::type_subtype_t& virus_type, const acmacs::virus::lineage_t& lineage);
}

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
