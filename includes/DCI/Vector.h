#ifndef DCI_VECTOR_H_INCLUDED
#define DCI_VECTOR_H_INCLUDED

#include "DCI/DCI.h"

namespace DCI {

// Forward declarations

class String;
class Value;

// {internal}
// Description: Vector Representation Implementation Template. 
//
// Every vector contains a reference to an instance of this class.
// As long as the vector content is not changed, multiple vectors may reference the same VectorRepBase instance.
// If one vector changes its contents and there are other references to its VectorRepBase, the VectorRepBase 
// instance is cloned.
struct DCI_DLLEXPORT VectorRepBase {
    VectorRepBase() : m_Len(0), m_RefCount(1) {}

    virtual VectorRepBase *Clone() = 0;
    virtual void           Destroy();
    virtual void           ReSize(size_t Len) = 0;
    virtual void           ReSize(size_t Len, const Value &InitVal) = 0;
    virtual size_t         GetSize(size_t Len) const = 0;
    virtual Bool           SaveToBinaryFile(FILE *fp) const = 0;

    size_t m_Len;
    int    m_RefCount;
    char   m_Data[1];
};

// {internal}
// Description:
// Vector representation implementation template for primitve data types. 
// Primitive data types are those that can be copied using memcpy().
template<class T> struct PVectorRep : public VectorRepBase {
    virtual VectorRepBase *Clone();
    virtual void           ReSize(size_t Len);
    virtual void           ReSize(size_t Len, const Value &InitVal);
    virtual size_t         GetSize(size_t Len) const;
    virtual Bool           SaveToBinaryFile(FILE *fp) const;
};

// {internal}
// Description:
// Vector representation implementation template for complex data types. 
// Complex data types are those that can not be copied using memcpy().
template<class T> struct CVectorRep : public VectorRepBase {
    virtual VectorRepBase *Clone();
    virtual void           Destroy();
    virtual void           ReSize(size_t Len);
    virtual void           ReSize(size_t Len, const Value &InitVal);
    virtual size_t         GetSize(size_t Len) const;
    virtual Bool           SaveToBinaryFile(FILE *fp) const;
};

// {internal}
// {group:Data Classes}
// Description: Vector Class.
//
// This class represents a vector of values with a variant data type 
// similar to a discriminated union (the discriminator being the data 
// type).
class DCI_DLLEXPORT Vector {
public:
	Vector() : m_DataType(DT_VOID), m_Rep(0) {}
    Vector(const Vector &v);
    Vector(FILE *fp);
    virtual ~Vector();

    Bool     SaveToBinaryFile(FILE *fp) const;
	DataType GetDataType() const { return m_DataType; }
	size_t   Len() const         { return m_Rep?m_Rep->m_Len:0; }
    Bool     ReDim(size_t Len);
    Bool     ReDim(size_t Len, const Value &InitVal);
	void     Clear()             { ReDim(0); }

    Vector &operator = (const Vector &v);
	
protected:
    Vector(DataType dt);
    Vector(DataType dt, const void *pValues, size_t Len, size_t Size);

	void CloneIfNeeded();

	DataType       m_DataType; // the vector's actual data type
    VectorRepBase *m_Rep;      // pointer the the variant vector representation
};

// {internal}
// Description: 
// Template implementation of class vector for primites data types.
// Primitive data types are those that can be copied using memcpy().
template<class T, DataType dt> class PTypedVector : public Vector {
public:
    PTypedVector() : Vector(dt) {
        if (m_Rep) ((PVectorRep<T> *)m_Rep)->PVectorRep<T>::PVectorRep();
    }
    PTypedVector(const Vector &v) : Vector(v) {}
    PTypedVector(const T *pValues, size_t Len) : Vector(dt, pValues, Len, Len * sizeof(T)) {
        if (!m_Rep) return;
        ((PVectorRep<T> *)m_Rep)->PVectorRep<T>::PVectorRep();
        m_Rep->m_Len = Len;
    }

	// accessors
	const T &operator[](size_t Index) const { 
		static T dummy;
		return (Index < m_Rep->m_Len) ? ((T *)m_Rep->m_Data)[Index] : dummy; 
	}
	T &operator [](size_t Index) {
		static T dummy;
		CloneIfNeeded();
		if (Index < m_Rep->m_Len) return ((T *)m_Rep->m_Data)[Index];
		return ReDim(Index+1) ? ((T *)m_Rep->m_Data)[Index] : dummy;
	}
	const T *GetPtr() const { return (T *)m_Rep->m_Data; }
    // {secret}
    // this method is currently not part of the DLL core interface
    Bool Remove(size_t Index) {
        size_t len = m_Rep->m_Len;
        if (Index < 0 || Index >= len) return false;
        CloneIfNeeded();
        T *p = ((T *)m_Rep->m_Data) + Index;
        memmove( p, p + 1, sizeof(T) * (len - Index - 1) );
        ReDim(len - 1);
        return true;
    }
};

// {internal}
// Description: 
// Template implementation of class vector for complex data types.
// Complex data types are those that can not be copied using memcpy().
template<class T, DataType dt> class CTypedVector : public Vector {
public:
    CTypedVector() : Vector(dt) {
        if (m_Rep) ((CVectorRep<T> *)m_Rep)->CVectorRep<T>::CVectorRep();
    }
    CTypedVector(const Vector &v) : Vector(v) {}

	// accessors
	const T &operator[](size_t Index) const { 
		static T dummy;
		return (Index < m_Rep->m_Len) ? ((T *)m_Rep->m_Data)[Index] : dummy; 
	}
	T &operator [](size_t Index) {
		static T dummy;
		CloneIfNeeded();
		if (Index < m_Rep->m_Len) return ((T *)m_Rep->m_Data)[Index];
		return ReDim(Index+1) ? ((T *)m_Rep->m_Data)[Index] : dummy;
	}
	const T *GetPtr() const { return (T *)m_Rep->m_Data; }
    // {secret}
    // this method is currently not part of the DLL core interface
    Bool Remove(size_t Index) {
        size_t len = m_Rep->m_Len;
        if (Index < 0 || Index >= len) return false;
        CloneIfNeeded();
        T *p = ((T *)m_Rep->m_Data) + Index;
        for (size_t i = Index + 1; i < len; i++, p++) p[0] = p[1];
        ReDim(len - 1);
        return true;
    }
};

// {group:Data Classes}
// {glyph:CPPClass|Class}
// Description: Byte Vector (Signed).
typedef PTypedVector <Byte, DT_BYTE> ByteVector;

// {group:Data Classes}
// {glyph:CPPClass|Class}
// Description: Integer Vector (Signed).
typedef PTypedVector <Int, DT_INT> IntVector;

// {group:Data Classes}
// {glyph:CPPClass|Class}
// Description: Double Precision Floating Point Vector.
typedef PTypedVector <Double, DT_DOUBLE> DoubleVector;

// {group:Data Classes}
// {glyph:CPPClass|Class}
// Description: String Vector.
typedef CTypedVector<String, DT_STRING> StringVector;

// {group:Data Classes}
// {glyph:CPPClass|Class}
// Description: Value Vector (Variant Typed Values).
typedef CTypedVector<Value, DT_VALUE> ValueVector;

} /* namespace DCI */

#endif /* DCI_VECTOR_H_INCLUDED */
