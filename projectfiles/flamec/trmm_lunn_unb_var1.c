
/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Akshar, Akshay , Zaid
                  ak52397@utexas.edu
                                                                     */

#include "FLAME.h"

int trmm_lunn_unb_var1( FLA_Obj U, FLA_Obj B )
{
  FLA_Obj UTL,   UTR,      U00,  u01,       U02, 
          UBL,   UBR,      u10t, upsilon11, u12t,
                           U20,  u21,       U22;

  FLA_Obj BT,              B0,
          BB,              b1t,
                           B2;

  FLA_Part_2x2( U,    &UTL, &UTR,
                      &UBL, &UBR,     0, 0, FLA_TL );

  FLA_Part_2x1( B,    &BT, 
                      &BB,            0, FLA_TOP );

  while ( FLA_Obj_length( UTL ) < FLA_Obj_length( U ) ){

    FLA_Repart_2x2_to_3x3( UTL, /**/ UTR,       &U00,  /**/ &u01,       &U02,
                        /* ************* */   /* **************************** */
                                                &u10t, /**/ &upsilon11, &u12t,
                           UBL, /**/ UBR,       &U20,  /**/ &u21,       &U22,
                           1, 1, FLA_BR );

    FLA_Repart_2x1_to_3x1( BT,                &B0, 
                        /* ** */            /* *** */
                                              &b1t, 
                           BB,                &B2,        1, FLA_BOTTOM );

    /*------------------------------------------------------------*/

    //  B0 = B0 + u01*b1t;
      FLA_Ger( FLA_ONE, u01, b1t, B0 );
      FLA_Scal( upsilon11, b1t );

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x3_to_2x2( &UTL, /**/ &UTR,       U00,  u01,       /**/ U02,
                                                     u10t, upsilon11, /**/ u12t,
                            /* ************** */  /* ************************** */
                              &UBL, /**/ &UBR,       U20,  u21,       /**/ U22,
                              FLA_TL );

    FLA_Cont_with_3x1_to_2x1( &BT,                B0, 
                                                  b1t, 
                            /* ** */           /* *** */
                              &BB,                B2,     FLA_TOP );

  }

  return FLA_SUCCESS;
}

