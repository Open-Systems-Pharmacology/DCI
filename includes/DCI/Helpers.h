#ifndef DCI_HELPERS_H_INCLUDED
#define DCI_HELPERS_H_INCLUDED

#include "DCI/DCI.h"

#include <string>
#include <sstream>
#include <COMUTIL.H>

// Value conversions Help Functions
std::string  ToString(DCI::Value val);
void         EncodeString(const DCI::String &source, DCI::String & target);
void         DecodeString(const DCI::String &source, DCI::String & target);
DCI::Value   FromVariant(_variant_t vt);
_variant_t   ToVariant(DCI::Value val=DCI::Value());

#endif