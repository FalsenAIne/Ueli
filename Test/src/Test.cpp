#include "Config.h"

#include "Ueli.h"

#ifdef UELI_TEST

#define BOOST_TEST_MODULE UeliTests
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(matrix_construction_test)
{
    Ueli::Math::Matrix mat1(4, 5);
    BOOST_CHECK(mat1.GetRows() == 4);
    BOOST_CHECK(mat1.GetColumns() == 5);
    BOOST_CHECK(mat1.GetElementCount() == 4 * 5);
}
BOOST_AUTO_TEST_CASE(matrix_operator_test)
{
    Ueli::Math::Matrix mat1(3, 5);
    mat1.Ones();
    BOOST_CHECK(mat1(2, 4)== 1);
    BOOST_CHECK(mat1(2, 0) == 1);
    BOOST_CHECK(mat1(0, 4) == 1);
}

BOOST_AUTO_TEST_CASE(matrix_data_test)
{
    Ueli::Math::Matrix mat1(2, 3);
    mat1.Zeros();

    float test_data1[6];
    for (int i = 0; i < 6; i++)
        test_data1[i] = mat1.GetData()[i];

    float data2[6] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    BOOST_TEST(test_data1 == data2, boost::test_tools::per_element());

    //==================================================================

    mat1.Ones();
    for (int i = 0; i < 6; i++)
        test_data1[i] = mat1.GetData()[i];

    float data3[6] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

    BOOST_TEST(test_data1 == data3, boost::test_tools::per_element());

    //==================================================================

    float data4[6] = { 1.4f, 74.3f, 17.5f, -1.0f, -0.54f, 176.0f };
    mat1.SetData(data4, 6);

    for (int i = 0; i < 6; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data4, boost::test_tools::per_element());

    //==================================================================

    Ueli::Math::Matrix mat2(3, 3);
    mat2.Diagonal();

    float data5[9] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
    float test_data2[9];

    for (int i = 0; i < 9; i++)
        test_data2[i] = mat2.GetData()[i];

    BOOST_TEST(test_data2 == data5, boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(matrix_to_string_test)
{
    Ueli::Math::Matrix mat1(3, 2);
    float data[6] = { 1.4f, 74.3f, 17.5f, -1.3f, -0.54f, 176.1f };
    mat1.SetData(data, 6);

    std::string string1 = { "1.4 74.3 \n17.5 -1.3 \n-0.54 176.1 \n" };

    BOOST_TEST(mat1.ToString() == string1);

    //==================================================================

    Ueli::Math::Matrix mat2(4, 4);
    mat2.Ones();
    std::string string2 = { "1 1 1 1 \n1 1 1 1 \n1 1 1 1 \n1 1 1 1 \n" };

    BOOST_TEST(mat2.ToString() == string2);
}

BOOST_AUTO_TEST_CASE(matrix_mul_test)
{
    Ueli::Math::Matrix mat1(2, 3);
    mat1.Ones();
    
    Ueli::Math::Matrix mat2(3, 4);
    mat2.Ones();
    
    Ueli::Math::Matrix mat3(2, 4);
    mat3.Mul(mat1, mat2);
    float data1[8] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
    float test_data1[8];
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat3.GetData()[i];
    
    BOOST_TEST(test_data1 == data1);
    
    //==================================================================
  
    mat2.Zeros();

    mat3.Mul(mat1, mat2);
    float data2[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat3.GetData()[i];

    BOOST_TEST(test_data1 == data2);

    //==================================================================


    Ueli::Math::Matrix mat4(3, 3);
    mat4.Diagonal();

    Ueli::Math::Matrix mat5(3, 3);
    mat5.Ones();

    Ueli::Math::Matrix mat6(3, 3);
    mat6.Mul(mat4, mat5);

    float data3[9] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
    float test_data2[9];

    for (int i = 0; i < 9; i++)
        test_data2[i] = mat6.GetData()[i];

    BOOST_TEST(test_data2 == data3);
}

BOOST_AUTO_TEST_CASE(matrix_elemantwise_matrix_test)
{
    float data1[8] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
    float data2[8] = { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f };

    Ueli::Math::Matrix mat1(2, 4);
    mat1.SetData(data1, 8);

    Ueli::Math::Matrix mat2(2, 4);
    mat2.SetData(data2, 8);

    mat1.Add(mat2);
    float data3[8] = { 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f };
    float test_data1[8];
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data3);

    //==================================================================
    
    mat1.Subtract(mat2);
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data1);

    //==================================================================

    mat1.Multiply(mat2);
    float data4[8] = { 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f };
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data4);

    //==================================================================

    Ueli::Math::Matrix mat3(1, 4);
    mat3.Ones();

    mat1.AddVector(mat3);
    float data5[8] = { 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f, 7.0f };

    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data5);
}

BOOST_AUTO_TEST_CASE(matrix_elemantwise_scalar_test)
{
    float data1[8] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
    float data2[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    Ueli::Math::Matrix mat1(2, 4);
    mat1.SetData(data1, 8);

    mat1.Add(2.0f);
    float data3[8] = { 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f };
    float test_data1[8];
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data3);

    //==================================================================

    mat1.Subtract(2.0f);
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data1);

    //==================================================================

    mat1.Multiply(2.0f);
    float data4[8] = { 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f };
    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data4);

    //==================================================================

    mat1.Multiply(0.0f);

    for (int i = 0; i < 8; i++)
        test_data1[i] = mat1.GetData()[i];

    BOOST_TEST(test_data1 == data2);
}

BOOST_AUTO_TEST_CASE(matrix_apply_function_test)
{
    float data1[8] = { 3.0f, 3.0f, 3.0f, 3.0f, -3.0f, -3.0f, -3.0f, -3.0f };
    float data2[8] = { 3.0f, 3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    Ueli::Math::Matrix mat1(2, 4);
    mat1.SetData(data1, 8);
    Ueli::Math::Matrix mat2(2, 4);

    mat2.ApplyFunction(mat1, Ueli::Network::ReLU);

    float test_data[8];
    for (int i = 0; i < 8; i++)
        test_data[i] = mat2.GetData()[i];

    BOOST_TEST(test_data == data2);
    
}

BOOST_AUTO_TEST_CASE(ReLU_test)
{
    BOOST_TEST(0.0f == Ueli::Network::ReLU(-13.0f));
    BOOST_TEST(7.0f == Ueli::Network::ReLU(7.0f));

}


#endif


    // seven ways to detect and report the same error:
    //BOOST_CHECK(add(2, 2) == 4);        // #1 continues on error
    //
    //BOOST_REQUIRE(add(2, 2) == 4);      // #2 throws on error
    //
    //if (add(2, 2) != 4)
    //    BOOST_ERROR("Ouch...");            // #3 continues on error
    //
    //if (add(2, 2) != 4)
    //    BOOST_FAIL("Ouch...");             // #4 throws on error
    //
    //if (add(2, 2) != 4) throw "Ouch..."; // #5 throws on error
    //
    //BOOST_CHECK_MESSAGE(add(2, 2) == 4,  // #6 continues on error
    //    "add(..) result: " << add(2, 2));
    //
    //BOOST_CHECK_EQUAL(add(2, 2), 4);	  // #7 continues on error