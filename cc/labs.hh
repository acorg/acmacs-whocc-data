#pragma once

#include "acmacs-chart-2/lab.hh"

// ----------------------------------------------------------------------

namespace acmacs::whocc::inline v1
{
    using Lab = acmacs::chart::Lab;

    const Lab& lab_name_normalize(const Lab& lab);
    Lab lab_name_normalize(std::string_view lab);
    const Lab& lab_name_old(const Lab& lab);

    extern const Lab CDC, CNIC, CRICK, NIID, VIDRL, MELB, NIMR;

} // namespace acmacs::whocc::inline v1

// ----------------------------------------------------------------------
/// Local Variables:
/// eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
/// End:
