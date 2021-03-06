
#include <UT/UT_DSOVersion.h>
#include <GU/GU_Detail.h>
#include <GU/GU_PrimVolume.h>
#include <GEO/GEO_AttributeHandle.h>
#include <GEO/GEO_IOTranslator.h>
#include <SOP/SOP_Node.h>
#include <UT/UT_Assert.h>
#include <UT/UT_IOTable.h>
#include <iostream>
#include <fstream>

#include "binarymesh.h"

namespace HAPS_HDK 
{

class GEO_HAPSIOTranslator : public GEO_IOTranslator
{
public:
             GEO_HAPSIOTranslator() {}
    virtual ~GEO_HAPSIOTranslator() {}
    virtual GEO_IOTranslator *duplicate() const;
    virtual const char *formatName() const;
    virtual int         checkExtension(const char *name);
    virtual int         checkMagicNumber(unsigned magic);
    virtual GA_Detail::IOStatus fileLoad(GEO_Detail *gdp, UT_IStream &is, bool ate_magic);
    virtual GA_Detail::IOStatus fileSave(const GEO_Detail *gdp, std::ostream &os);
    virtual GA_Detail::IOStatus fileSaveToFile(const GEO_Detail *gdp, const char *fname);
};
}

using namespace HAPS_HDK;

GEO_IOTranslator *
GEO_HAPSIOTranslator::duplicate() const
{
    return new GEO_HAPSIOTranslator();
}
const char *
GEO_HAPSIOTranslator::formatName() const
{
    return "Appleseed binarymesh";
}
int
GEO_HAPSIOTranslator::checkExtension(const char *name) 
{
    UT_String           sname(name);
    if (sname.fileExtension() && !strcmp(sname.fileExtension(), ".binarymesh"))
        return true;
    return false;
}
int
GEO_HAPSIOTranslator::checkMagicNumber(unsigned magic)
{
    return 0;
}
GA_Detail::IOStatus
GEO_HAPSIOTranslator::fileLoad(GEO_Detail *gdp, UT_IStream &is, bool ate_magic)
{
    std::cerr << "Error: Not impemented yet.\n";
    return false;

}
GA_Detail::IOStatus
GEO_HAPSIOTranslator::fileSave(const GEO_Detail *gdp, std::ostream &os)
{
    bool result = false;
    if (os) {
        result = save_binarymesh(os, gdp);
    } 
    return result;
}

GA_Detail::IOStatus
GEO_HAPSIOTranslator::fileSaveToFile(const GEO_Detail *gdp, const char *filename)
{
    if (!filename)
        return false;

    auto result = GA_Detail::IOStatus(false);
    auto stream = std::ofstream(filename, std::ios::out | std::ios::binary);
    if (stream.is_open()) {
         result = fileSave(gdp, stream);
        stream.close();
    }
    return result;
}

void
newGeometryIO(void *)
{
    GU_Detail::registerIOTranslator(new GEO_HAPSIOTranslator());
    UT_ExtensionList            *geoextension;
    geoextension = UTgetGeoExtensions();
    if (!geoextension->findExtension("binarymesh"))
        geoextension->addExtension("binarymesh");
}