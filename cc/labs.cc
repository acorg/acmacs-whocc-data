#include "acmacs-base/string.hh"
#include "acmacs-whocc-data/labs.hh"

// ----------------------------------------------------------------------

#include "acmacs-base/global-constructors-push.hh"

namespace acmacs::whocc::inline v1
{
    const Lab CDC{"CDC"}, CNIC{"CNIC"}, CRICK{"Crick"}, NIID{"NIID"}, VIDRL{"VIDRL"}, MELB{"MELB"}, NIMR{"NIMR"};

    static const Lab CRICK_U{"CRICK"};

} // namespace acmacs::whocc::inline v1

#include "acmacs-base/diagnostics-pop.hh"

// ----------------------------------------------------------------------

const acmacs::Lab& acmacs::whocc::v1::lab_name_normalize(const Lab& lab)
{
    if (lab == NIMR || lab == CRICK_U)
        return CRICK;
    else if (lab == MELB)
        return VIDRL;
    else
        return lab;

} // acmacs::whocc::v1::lab_name_normalize

// ----------------------------------------------------------------------

acmacs::Lab acmacs::whocc::v1::lab_name_normalize(std::string_view lab)
{
    return lab_name_normalize(Lab{::string::upper(lab)});

} // acmacs::whocc::v1::lab_name_normalize

// ----------------------------------------------------------------------

const acmacs::Lab& acmacs::whocc::v1::lab_name_old(const Lab& lab)
{
    if (lab == CRICK || lab == CRICK_U)
        return NIMR;
    else if (lab == VIDRL)
        return MELB;
    else
        return lab;

} // acmacs::whocc::v1::lab_name_old

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
