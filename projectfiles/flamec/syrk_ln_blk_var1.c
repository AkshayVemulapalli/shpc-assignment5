/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Akshar, Akshay, Zaid
                ak52397@utexas.edu
                                                                     */

#include "FLAME.h"

int syrk_ln_blk_var1( FLA_Obj C, FLA_Obj A)
{
  FLA_Obj CTL,   CTR,      C00, C01, C02, 
          CBL,   CBR,      C10, C11, C12,
                           C20, C21, C22;

  FLA_Obj AT,              A0,
          AB,              A1,
                           A2;

  int b;

  FLA_Part_2x2( C,    &CTL, &CTR,
                      &CBL, &CBR,     0, 0, FLA_TR );

  FLA_Part_2x1( A,    &AT, 
                      &AB,            0, FLA_TOP );

  while ( FLA_Obj_length( CTR ) < FLA_Obj_length( C ) ){

    //b = min( FLA_Obj_length( CBL ), nb_alg );
    b = (FLA_Obj_length( CBL ));

    FLA_Repart_2x2_to_3x3( CTL, /**/ CTR,       &C00, &C01, /**/ &C02,
                        /* ************* */   /* ******************** */
                                                &C10, &C11, /**/ &C12,
                           CBL, /**/ CBR,       &C20, &C21, /**/ &C22,
                           b, b, FLA_BL );

    FLA_Repart_2x1_to_3x1( AT,                &A0, 
                        /* ** */            /* ** */
                                              &A1, 
                           AB,                &A2,        b, FLA_BOTTOM );

    /*------------------------------------------------------------*/

    // C21 = A2 * A1^T + C21
    FLA_Gemm( FLA_NO_TRANSPOSE, FLA_TRANSPOSE, FLA_ONE, A2, A1, FLA_ONE, C21 );
    // C11 = A1 * A1^T + C11
    /* C = tril( A * A' + C  ) + triu( C, -1 )? */
    FLA_Syrk( FLA_LOWER_TRIANGULAR, FLA_NO_TRANSPOSE, 
      FLA_ONE, A1, FLA_ONE, C11);

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x3_to_2x2( &CTL, /**/ &CTR,       C00, /**/ C01, C02,
                                                     C10, /**/ C11, C12,
                            /* ************** */  /* ****************** */
                              &CBL, /**/ &CBR,       C20, /**/ C21, C22,
                              FLA_TR );

    FLA_Cont_with_3x1_to_2x1( &AT,                A0, 
                                                  A1, 
                            /* ** */           /* ** */
                              &AB,                A2,     FLA_TOP );

  }

  return FLA_SUCCESS;
}

