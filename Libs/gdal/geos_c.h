/************************************************************************
 *
 * $Id: geos_c.h.in 2027 2007-09-21 17:40:15Z csavage $
 *
 * C-Wrapper for GEOS library
 *
 * Copyright (C) 2005 Refractions Research Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 * Author: Sandro Santilli <strk@refractions.net>
 *
 ***********************************************************************
 *
 * GENERAL NOTES:
 *
 *	- Remember to call initGEOS() before any use of this library's
 *	  functions, and call finishGEOS() when done.
 *
 *	- Currently you have to explicitly GEOSGeom_destroy() all
 *	  GEOSGeom objects to avoid memory leaks, and to free()
 *	  all returned char * (unless const). This might change
 *	  before first release to ensure greater API stability.
 *
 ***********************************************************************/

#ifndef GEOS_C_H
#define GEOS_C_H

#ifndef __cplusplus
# include <stddef.h> /* for size_t definition */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 *
 * Version
 *
 ***********************************************************************/

/*
 * Following 'ifdef' hack fixes problem with generating geos_c.h on Windows,
 * when building with Visual C++ compiler.
 */
#if defined(_MSC_VER)
#include <geos/version.h>
#define GEOS_CAPI_VERSION_MAJOR 1
#define GEOS_CAPI_VERSION_MINOR 3
#define GEOS_CAPI_VERSION_PATCH 3
#define GEOS_CAPI_VERSION "3.0.3-CAPI-1.3.3"
#else
#define GEOS_VERSION_MAJOR @VERSION_MAJOR@
#define GEOS_VERSION_MINOR @VERSION_MINOR@
#define GEOS_VERSION_PATCH @VERSION_PATCH@
#define GEOS_VERSION "@VERSION@"
#define GEOS_JTS_PORT "@JTS_PORT@"

#define GEOS_CAPI_VERSION_MAJOR @CAPI_VERSION_MAJOR@
#define GEOS_CAPI_VERSION_MINOR @CAPI_VERSION_MINOR@
#define GEOS_CAPI_VERSION_PATCH @CAPI_VERSION_PATCH@
#define GEOS_CAPI_VERSION "@VERSION@-CAPI-@CAPI_VERSION@"
#endif 

#define GEOS_CAPI_FIRST_INTERFACE GEOS_CAPI_VERSION_MAJOR 
#define GEOS_CAPI_LAST_INTERFACE (GEOS_CAPI_VERSION_MAJOR+GEOS_CAPI_VERSION_MINOR)
 
/************************************************************************
 *
 * (Abstract) type definitions
 *
 ***********************************************************************/

typedef void (*GEOSMessageHandler)(const char *fmt, ...);

/* When we're included by geos_c.cpp, those are #defined to the original
 * JTS definitions via preprocessor. We don't touch them to allow the
 * compiler to cross-check the declarations. However, for all "normal" 
 * C-API users, we need to define them as "opaque" struct pointers, as 
 * those clients don't have access to the original C++ headers, by design.
 */
#ifndef GEOSGeometry
typedef struct GEOSGeom_t GEOSGeometry;
typedef struct GEOSCoordSeq_t GEOSCoordSequence;
#endif

/* Those are compatibility definitions for source compatibility
 * with GEOS 2.X clients relying on that type.
 */
typedef GEOSGeometry* GEOSGeom;
typedef GEOSCoordSequence* GEOSCoordSeq;

/* Supported geometry types
 * This was renamed from GEOSGeomTypeId in GEOS 2.2.X, which might
 * break compatibility, this issue is still under investigation.
 */

enum GEOSGeomTypes {
	GEOS_POINT,
	GEOS_LINESTRING,
	GEOS_LINEARRING,
	GEOS_POLYGON,
	GEOS_MULTIPOINT,
	GEOS_MULTILINESTRING,
	GEOS_MULTIPOLYGON,
	GEOS_GEOMETRYCOLLECTION
};

/* Byte oders exposed via the c api */
enum GEOSByteOrders {
	GEOS_WKB_XDR = 0, /* Big Endian */
	GEOS_WKB_NDR = 1 /* Little Endian */
};


/************************************************************************
 *
 * Initialization, cleanup, version
 *
 ***********************************************************************/

#if defined(_MSC_VER)
#  define GEOS_DLL     __declspec(dllexport)
#else
#  define GEOS_DLL
#endif

extern void GEOS_DLL initGEOS(GEOSMessageHandler notice_function,
	GEOSMessageHandler error_function);
extern void GEOS_DLL finishGEOS(void);
extern const char GEOS_DLL *GEOSversion();


/************************************************************************
 *
 * NOTE - These functions are DEPRECATED.  Please use the new Reader and
 * writer APIS!
 *
 ***********************************************************************/

extern GEOSGeometry GEOS_DLL *GEOSGeomFromWKT(const char *wkt);
extern char GEOS_DLL *GEOSGeomToWKT(const GEOSGeometry* g);

/*
 * Specify whether output WKB should be 2d or 3d.
 * Return previously set number of dimensions.
 */
extern int GEOS_DLL GEOS_getWKBOutputDims();
extern int GEOS_DLL GEOS_setWKBOutputDims(int newDims);

/*
 * Specify whether the WKB byte order is big or little endian. 
 * The return value is the previous byte order.
 */
extern int GEOS_DLL GEOS_getWKBByteOrder();
extern int GEOS_DLL GEOS_setWKBByteOrder(int byteOrder);

extern GEOSGeometry GEOS_DLL *GEOSGeomFromWKB_buf(const unsigned char *wkb, size_t size);
extern unsigned char GEOS_DLL *GEOSGeomToWKB_buf(const GEOSGeometry* g, size_t *size);

extern GEOSGeometry GEOS_DLL *GEOSGeomFromHEX_buf(const unsigned char *hex, size_t size);
extern unsigned char GEOS_DLL *GEOSGeomToHEX_buf(const GEOSGeometry* g, size_t *size);

/************************************************************************
 *
 * Coordinate Sequence functions
 *
 ***********************************************************************/

/*
 * Create a Coordinate sequence with ``size'' coordinates
 * of ``dims'' dimensions.
 * Return NULL on exception.
 */
extern GEOSCoordSequence GEOS_DLL *GEOSCoordSeq_create(unsigned int size, unsigned int dims);

/*
 * Clone a Coordinate Sequence.
 * Return NULL on exception.
 */
extern GEOSCoordSequence GEOS_DLL *GEOSCoordSeq_clone(const GEOSCoordSequence* s);

/*
 * Destroy a Coordinate Sequence.
 */
extern void GEOS_DLL GEOSCoordSeq_destroy(GEOSCoordSequence* s);

/*
 * Set ordinate values in a Coordinate Sequence.
 * Return 0 on exception.
 */
extern int GEOS_DLL GEOSCoordSeq_setX(GEOSCoordSequence* s,
	unsigned int idx, double val);
extern int GEOS_DLL GEOSCoordSeq_setY(GEOSCoordSequence* s,
	unsigned int idx, double val);
extern int GEOS_DLL GEOSCoordSeq_setZ(GEOSCoordSequence* s,
	unsigned int idx, double val);
extern int GEOS_DLL GEOSCoordSeq_setOrdinate(GEOSCoordSequence* s,
	unsigned int idx, unsigned int dim, double val);

/*
 * Get ordinate values from a Coordinate Sequence.
 * Return 0 on exception.
 */
extern int GEOS_DLL GEOSCoordSeq_getX(const GEOSCoordSequence* s,
	unsigned int idx, double *val);
extern int GEOS_DLL GEOSCoordSeq_getY(const GEOSCoordSequence* s,
	unsigned int idx, double *val);
extern int GEOS_DLL GEOSCoordSeq_getZ(const GEOSCoordSequence* s,
	unsigned int idx, double *val);
extern int GEOS_DLL GEOSCoordSeq_getOrdinate(const GEOSCoordSequence* s,
	unsigned int idx, unsigned int dim, double *val);

/*
 * Get size and dimensions info from a Coordinate Sequence.
 * Return 0 on exception.
 */
extern int GEOS_DLL GEOSCoordSeq_getSize(const GEOSCoordSequence* s,
	unsigned int *size);
extern int GEOS_DLL GEOSCoordSeq_getDimensions(const GEOSCoordSequence* s,
	unsigned int *dims);


/************************************************************************
 *
 * Geometry Constructors.
 * GEOSCoordSequence* arguments will become ownership of the returned object.
 * All functions return NULL on exception.
 *
 ***********************************************************************/

extern GEOSGeometry GEOS_DLL *GEOSGeom_createPoint(GEOSCoordSequence* s);
extern GEOSGeometry GEOS_DLL *GEOSGeom_createLinearRing(GEOSCoordSequence* s);
extern GEOSGeometry GEOS_DLL *GEOSGeom_createLineString(GEOSCoordSequence* s);

/*
 * Second argument is an array of GEOSGeometry* objects.
 * The caller remains owner of the array, but pointed-to
 * objects become ownership of the returned GEOSGeometry.
 */
extern GEOSGeometry GEOS_DLL *GEOSGeom_createPolygon(GEOSGeometry* shell,
	GEOSGeometry** holes, unsigned int nholes);
extern GEOSGeometry GEOS_DLL *GEOSGeom_createCollection(int type,
	GEOSGeometry* *geoms, unsigned int ngeoms);

extern GEOSGeometry GEOS_DLL *GEOSGeom_clone(const GEOSGeometry* g);

/************************************************************************
 *
 * Memory management
 *
 ***********************************************************************/

extern void GEOS_DLL GEOSGeom_destroy(GEOSGeometry* g);


/************************************************************************
 *
 * Topology operations - return NULL on exception.
 *
 ***********************************************************************/

extern GEOSGeometry GEOS_DLL *GEOSEnvelope(const GEOSGeometry* g1);
extern GEOSGeometry GEOS_DLL *GEOSIntersection(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern GEOSGeometry GEOS_DLL *GEOSBuffer(const GEOSGeometry* g1,
	double width, int quadsegs);
extern GEOSGeometry GEOS_DLL *GEOSConvexHull(const GEOSGeometry* g1);
extern GEOSGeometry GEOS_DLL *GEOSDifference(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern GEOSGeometry GEOS_DLL *GEOSSymDifference(const GEOSGeometry* g1,
	const GEOSGeometry* g2);
extern GEOSGeometry GEOS_DLL *GEOSBoundary(const GEOSGeometry* g1);
extern GEOSGeometry GEOS_DLL *GEOSUnion(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern GEOSGeometry GEOS_DLL *GEOSPointOnSurface(const GEOSGeometry* g1);
extern GEOSGeometry GEOS_DLL *GEOSGetCentroid(const GEOSGeometry* g);
extern char GEOS_DLL *GEOSRelate(const GEOSGeometry* g1, const GEOSGeometry* g2);

/*
 * all arguments remain ownership of the caller
 * (both Geometries and pointers)
 */
extern GEOSGeometry GEOS_DLL *GEOSPolygonize(const GEOSGeometry * const geoms[],
	unsigned int ngeoms);

extern GEOSGeometry GEOS_DLL *GEOSLineMerge(const GEOSGeometry* g);
extern GEOSGeometry GEOS_DLL *GEOSSimplify(const GEOSGeometry* g1, double tolerance);
extern GEOSGeometry GEOS_DLL *GEOSTopologyPreserveSimplify(const GEOSGeometry* g1,
	double tolerance);

/************************************************************************
 *
 *  Binary predicates - return 2 on exception, 1 on true, 0 on false
 *
 ***********************************************************************/

extern char GEOS_DLL GEOSRelatePattern(const GEOSGeometry* g1, const GEOSGeometry* g2,
	const char *pat);
extern char GEOS_DLL GEOSDisjoint(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSTouches(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSIntersects(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSCrosses(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSWithin(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSContains(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSOverlaps(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSEquals(const GEOSGeometry* g1, const GEOSGeometry* g2);
extern char GEOS_DLL GEOSEqualsExact(const GEOSGeometry* g1, const GEOSGeometry* g2, double tolerance);


/************************************************************************
 *
 *  Unary predicate - return 2 on exception, 1 on true, 0 on false
 *
 ***********************************************************************/

extern char GEOS_DLL GEOSisEmpty(const GEOSGeometry* g1);
extern char GEOS_DLL GEOSisValid(const GEOSGeometry* g1);
extern char GEOS_DLL GEOSisSimple(const GEOSGeometry* g1);
extern char GEOS_DLL GEOSisRing(const GEOSGeometry* g1);
extern char GEOS_DLL GEOSHasZ(const GEOSGeometry* g1);


/************************************************************************
 *
 *  Geometry info
 *
 ***********************************************************************/

/* Return NULL on exception, result must be freed by caller. */
extern char GEOS_DLL *GEOSGeomType(const GEOSGeometry* g1);

/* Return -1 on exception */
extern int GEOS_DLL GEOSGeomTypeId(const GEOSGeometry* g1);

/* Return 0 on exception */
extern int GEOS_DLL GEOSGetSRID(const GEOSGeometry* g1);

extern void GEOS_DLL GEOSSetSRID(GEOSGeometry* g, int SRID);

/* May be called on all geometries in GEOS 3.x, returns -1 on error and 1
 * for non-multi geometries. Older GEOS versions only accept 
 * GeometryCollections or Multi* geometries here, and are likely to crash
 * when feeded simple geometries, so beware if you need compatibility with
 * old GEOS versions.
 */
extern int GEOS_DLL GEOSGetNumGeometries(const GEOSGeometry* g1);

/*
 * Return NULL on exception, Geometry must be a Collection.
 * Returned object is a pointer to internal storage:
 * it must NOT be destroyed directly.
 */
extern const GEOSGeometry GEOS_DLL *GEOSGetGeometryN(const GEOSGeometry* g, int n);

/* Return -1 on exception */
extern int GEOS_DLL GEOSNormalize(GEOSGeometry* g1);

/* Return -1 on exception */
extern int GEOS_DLL GEOSGetNumInteriorRings(const GEOSGeometry* g1);

/*
 * Return NULL on exception, Geometry must be a Polygon.
 * Returned object is a pointer to internal storage:
 * it must NOT be destroyed directly.
 */
extern const GEOSGeometry GEOS_DLL *GEOSGetInteriorRingN(const GEOSGeometry* g, int n);

/*
 * Return NULL on exception, Geometry must be a Polygon.
 * Returned object is a pointer to internal storage:
 * it must NOT be destroyed directly.
 */
extern const GEOSGeometry GEOS_DLL *GEOSGetExteriorRing(const GEOSGeometry* g);

/* Return -1 on exception */
extern int GEOS_DLL GEOSGetNumCoordinates(const GEOSGeometry* g1);

/*
 * Return NULL on exception.
 * Geometry must be a LineString, LinearRing or Point.
 */
extern const GEOSCoordSequence GEOS_DLL *GEOSGeom_getCoordSeq(const GEOSGeometry* g);

/*
 * Return 0 on exception (or empty geometry)
 */
extern int GEOS_DLL GEOSGeom_getDimensions(const GEOSGeometry* g);

/************************************************************************
 *
 *  Misc functions 
 *
 ***********************************************************************/

/* Return 0 on exception, 1 otherwise */
extern int GEOS_DLL GEOSArea(const GEOSGeometry* g1, double *area);
extern int GEOS_DLL GEOSLength(const GEOSGeometry* g1, double *length);
extern int GEOS_DLL GEOSDistance(const GEOSGeometry* g1, const GEOSGeometry* g2,
	double *dist);



/************************************************************************
 *
 * Reader and Writer APIs
 *
 ***********************************************************************/

typedef struct GEOSWKTReader_t GEOSWKTReader;
typedef struct GEOSWKTWriter_t GEOSWKTWriter;
typedef struct GEOSWKBReader_t GEOSWKBReader;
typedef struct GEOSWKBWriter_t GEOSWKBWriter;


/* WKT Reader */
extern GEOSWKTReader GEOS_DLL *GEOSWKTReader_create();
extern void GEOS_DLL GEOSWKTReader_destroy(GEOSWKTReader* reader);
extern GEOSGeometry GEOS_DLL *GEOSWKTReader_read(GEOSWKTReader* reader, const char *wkt);

/* WKT Writer */
extern GEOSWKTWriter GEOS_DLL *GEOSWKTWriter_create();
extern void GEOS_DLL GEOSWKTWriter_destroy(GEOSWKTWriter* writer);
extern char GEOS_DLL *GEOSWKTWriter_write(GEOSWKTWriter* reader, const GEOSGeometry* g);

/* WKB Reader */
extern GEOSWKBReader GEOS_DLL *GEOSWKBReader_create();
extern void GEOS_DLL GEOSWKBReader_destroy(GEOSWKBReader* reader);
extern GEOSGeometry GEOS_DLL *GEOSWKBReader_read(GEOSWKBReader* reader, const unsigned char *wkb, size_t size);
extern GEOSGeometry GEOS_DLL *GEOSWKBReader_readHEX(GEOSWKBReader* reader, const unsigned char *hex, size_t size);

/* WKB Writer */
extern GEOSWKBWriter GEOS_DLL *GEOSWKBWriter_create();
extern void GEOS_DLL GEOSWKBWriter_destroy(GEOSWKBWriter* writer);

/* The owner owns the results for these two methods! */
extern unsigned char GEOS_DLL *GEOSWKBWriter_write(GEOSWKBWriter* writer, const GEOSGeometry* g, size_t *size);
extern unsigned char GEOS_DLL *GEOSWKBWriter_writeHEX(GEOSWKBWriter* writer, const GEOSGeometry* g, size_t *size);

/* 
 * Specify whether output WKB should be 2d or 3d.
 * Return previously set number of dimensions.
 */
extern int GEOS_DLL GEOSWKBWriter_getOutputDimension(const GEOSWKBWriter* writer);
extern void GEOS_DLL GEOSWKBWriter_setOutputDimension(GEOSWKBWriter* writer, int newDimension);

/*
 * Specify whether the WKB byte order is big or little endian. 
 * The return value is the previous byte order.
 */
extern int GEOS_DLL GEOSWKBWriter_getByteOrder(const GEOSWKBWriter* writer);
extern void GEOS_DLL GEOSWKBWriter_setByteOrder(GEOSWKBWriter* writer, int byteOrder);

/*
 * Specify whether SRID values should be output. 
 */
extern char GEOS_DLL GEOSWKBWriter_getIncludeSRID(const GEOSWKBWriter* writer);
extern void GEOS_DLL GEOSWKBWriter_setIncludeSRID(GEOSWKBWriter* writer, const char writeSRID);




#ifdef __cplusplus
} // extern "C"
#endif

#endif /* #ifndef GEOS_C_H */
