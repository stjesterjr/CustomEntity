#pragma once
#include <dbmain.h>

#include "dbmain.h"
#include "geassign.h"
#include "dbents.h"

#include "dbcurve.h"
#include "dbapserv.h"
#include "gegbl.h"
#include "gegblabb.h"
#include "gemat3d.h"
#include "acestext.h"
#include "gept2dar.h"
#include "windows.h"
#include "dbxutil.h"

class ASDKLink :
    public AcDbEntity
{
public:
    // ACRX_DECLARE_MEMBERS macro
    ACRX_DECLARE_MEMBERS(ASDKLink);

protected:
    static Adesk::UInt32 m_version;

public:
    ASDKLink();
    virtual ~ASDKLink();

    /////////////////////////////////////////////////////////
    // Methods specific to AcDbCrossCircleLink
    /////////////////////////////////////////////////////////
    // Data Members access functions

    AcGePoint3d link_start() const { return m_link_start; };
    Acad::ErrorStatus setStart(AcGePoint3d in) {
        m_link_start = in;
        return Acad::eOk;
    }
    AcGePoint3d link_end() const { return m_link_end; };
    Acad::ErrorStatus setEnd(AcGePoint3d in) {
        m_link_end = in;
        return Acad::eOk;
    }

    //----- AcDbObject protocols
    // Dwg
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
    // Dxf
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;


    //----- AcDbEntity protocols
    //- Graphics protocol
protected:
    Acad::ErrorStatus getVertices3d(AcGePoint3dArray& vertexArray) const;



    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode) override;
    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform) override;
    virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const override;

    //- Osnap points protocol
public:
    virtual Acad::ErrorStatus subGetOsnapPoints(
        AcDb::OsnapMode osnapMode,
        Adesk::GsMarker gsSelectionMark,
        const AcGePoint3d& pickPoint,
        const AcGePoint3d& lastPoint,
        const AcGeMatrix3d& viewXform,
        AcGePoint3dArray& snapPoints,
        AcDbIntArray& geomIds) const override;

    //- Grip points protocol
    virtual Acad::ErrorStatus subGetGripPoints(
        AcGePoint3dArray& gripPoints,
        AcDbIntArray& osnapModes,
        AcDbIntArray& geomIds) const override;

    virtual Acad::ErrorStatus subMoveGripPointsAt(
        const AcDbIntArray& indices,
        const AcGeVector3d& offset) override;

    virtual Acad::ErrorStatus subGetGripPoints(
        AcDbGripDataPtrArray& grips,
        const double curViewUnitSize,
        const int gripSize,
        const AcGeVector3d& curViewDir,
        const int bitflags) const override;

    virtual Acad::ErrorStatus subMoveGripPointsAt(
        const AcDbVoidPtrArray& gripAppData,
        const AcGeVector3d& offset,
        const int bitflags) override;

private:
    // Data Members
    AcGePoint3d m_link_start;
    AcGePoint3d m_link_end;
    AcDbLine* m_line;
};

