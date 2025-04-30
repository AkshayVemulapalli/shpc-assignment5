
/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Name of author
                  Email of author
                                                                     */

#include "FLAME.h"

int trmm_lunn(_B,_U_)_blk( FLA_Obj B, FLA_Obj U, int nb_alg )
{
  FLA_Obj BT,              B0,
          BB,              B1,
                           B2;

  FLA_Obj UTL,   UTR,      U00, U01, U02, 
          UBL,   UBR,      U10, U11, U12,
                           U20, U21, U22;

  int b;

  FLA_Part_2x1( B,    &BT, 
                      &BB,            0, FLA_TOP );

  FLA_Part_2x2( U,    &UTL, &UTR,
                      &UBL, &UBR,     0, 0, FLA_TL );

  while ( FLA_Obj_length( BT ) < FLA_Obj_length( B ) ){

    b = min( FLA_Obj_length( BB ), nb_alg );

    FLA_Repart_2x1_to_3x1( BT,                &B0, 
                        /* ** */            /* ** */
                                              &B1, 
                           BB,                &B2,        b, FLA_BOTTOM );

    FLA_Repart_2x2_to_3x3( UTL, /**/ UTR,       &U00, /**/ &U01, &U02,
                        /* ************* */   /* ******************** */
                                                &U10, /**/ &U11, &U12,
                           UBL, /**/ UBR,       &U20, /**/ &U21, &U22,
                           b, b, FLA_BR );

    /*------------------------------------------------------------*/

    //B0 = U01 * B1 + B0
    FLA_Gemm( FLA_NO_TRANSPOSE, FLA_NO_TRANSPOSE, FLA_ONE, A, B, FLA_ONE, C );

    //B1 = U11 * B1
    FLA_Trmm( FLA_LEFT, FLA_UPPER_TRIANGULAR, 
      FLA_NO_TRANSPOSE, FLA_NONUNIT_DIAG,
      FLA_ONE, U11, B1);

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x1_to_2x1( &BT,                B0, 
                                                  B1, 
                            /* ** */           /* ** */
                              &BB,                B2,     FLA_TOP );

    FLA_Cont_with_3x3_to_2x2( &UTL, /**/ &UTR,       U00, U01, /**/ U02,
                                                     U10, U11, /**/ U12,
                            /* ************** */  /* ****************** */
                              &UBL, /**/ &UBR,       U20, U21, /**/ U22,
                              FLA_TL );

  }

  return FLA_SUCCESS;
}

