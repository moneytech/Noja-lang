
#include "header.h"

Operator operator_matrix_add[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_add,
        // ObjectInt + ObjectFloat
        0,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        0,
        // ObjectFloat + ObjectFloat
        ObjectFloat_add,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        ObjectString_add,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }
};

Operator operator_matrix_sub[6][6] = {

    {
        // ObjectType - ObjectType
        0,
        // ObjectType - ObjectInt
        0,
        // ObjectType - ObjectFloat
        0,
        // ObjectType - ObjectString
        0,
        // ObjectType - Dict
        0,
        // ObjectArray - ObjectArray
        0

    }, {

        // ObjectInt - ObjectType
        0,
        // ObjectInt - ObjectInt
        ObjectInt_sub,
        // ObjectInt - ObjectFloat
        0,
        // ObjectInt - ObjectString
        0,
        // ObjectInt - Dict
        0,
        // ObjectArray - ObjectArray
        0

    }, {

        // ObjectFloat - ObjectType
        0,
        // ObjectFloat - ObjectInt
        0,
        // ObjectFloat - ObjectFloat
        ObjectFloat_sub,
        // ObjectFloat - ObjectString
        0,
        // ObjectFloat - Dict
        0,
        // ObjectArray - ObjectArray
        0

    }, {

        // ObjectString - ObjectType
        0,
        // ObjectString - ObjectInt
        0,
        // ObjectString - ObjectFloat
        0,
        // ObjectString - ObjectString
        0,
        // ObjectString - Dict
        0,
        // ObjectArray - ObjectArray
        0

    }, {

        // Dict - ObjectType
        0,
        // Dict - ObjectInt
        0,
        // Dict - ObjectFloat
        0,
        // Dict - ObjectString
        0,
        // Dict - Dict
        0,
        // ObjectArray - ObjectArray
        0

    }, {

        // ObjectArray - ObjectType
        0,
        // ObjectArray - ObjectInt
        0,
        // ObjectArray - ObjectFloat
        0,
        // ObjectArray - ObjectString
        0,
        // ObjectArray - Dict
        0,
        // ObjectArray - ObjectArray
        0

    }
};

Operator operator_matrix_mul[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_mul,
        // ObjectInt + ObjectFloat
        0,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        0,
        // ObjectFloat + ObjectFloat
        ObjectFloat_mul,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        0,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }
};

Operator operator_matrix_div[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_div,
        // ObjectInt + ObjectFloat
        0,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        0,
        // ObjectFloat + ObjectFloat
        ObjectFloat_div,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        0,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }
};


Operator operator_matrix_lss[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_lss,
        // ObjectInt + ObjectFloat
        ObjectIntObjectFloat_lss,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        ObjectFloatObjectInt_lss,
        // ObjectFloat + ObjectFloat
        ObjectFloat_lss,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        0,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }
};


Operator operator_matrix_leq[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_leq,
        // ObjectInt + ObjectFloat
        ObjectIntObjectFloat_leq,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        ObjectFloatObjectInt_leq,
        // ObjectFloat + ObjectFloat
        ObjectFloat_leq,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        0,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }
};


Operator operator_matrix_grt[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_grt,
        // ObjectInt + ObjectFloat
        ObjectIntObjectFloat_grt,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        ObjectFloatObjectInt_grt,
        // ObjectFloat + ObjectFloat
        ObjectFloat_grt,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        0,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }
};


Operator operator_matrix_geq[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_geq,
        // ObjectInt + ObjectFloat
        ObjectIntObjectFloat_geq,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        ObjectFloatObjectInt_geq,
        // ObjectFloat + ObjectFloat
        ObjectFloat_geq,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        0,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }
};



Operator operator_matrix_eql[6][6] = {

    {
        // ObjectType + ObjectType
        0,
        // ObjectType + ObjectInt
        0,
        // ObjectType + ObjectFloat
        0,
        // ObjectType + ObjectString
        0,
        // ObjectType + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectInt + ObjectType
        0,
        // ObjectInt + ObjectInt
        ObjectInt_eql,
        // ObjectInt + ObjectFloat
        0,
        // ObjectInt + ObjectString
        0,
        // ObjectInt + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectFloat + ObjectType
        0,
        // ObjectFloat + ObjectInt
        0,
        // ObjectFloat + ObjectFloat
        ObjectFloat_eql,
        // ObjectFloat + ObjectString
        0,
        // ObjectFloat + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectString + ObjectType
        0,
        // ObjectString + ObjectInt
        0,
        // ObjectString + ObjectFloat
        0,
        // ObjectString + ObjectString
        ObjectString_eql,
        // ObjectString + Dict
        0,
        // ObjectArray + ObjectArray
        0

    }, {

        // Dict + ObjectType
        0,
        // Dict + ObjectInt
        0,
        // Dict + ObjectFloat
        0,
        // Dict + ObjectString
        0,
        // Dict + Dict
        Dict_eql,
        // ObjectArray + ObjectArray
        0

    }, {

        // ObjectArray + ObjectType
        0,
        // ObjectArray + ObjectInt
        0,
        // ObjectArray + ObjectFloat
        0,
        // ObjectArray + ObjectString
        0,
        // ObjectArray + Dict
        0,
        // ObjectArray + ObjectArray
        ObjectArray_eql

    }
};
