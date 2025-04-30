
/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Akshar, Akshay, Zaid
                ak52397@utexas.edu
                                                                     */

#include "FLAME.h"

int trmm_lunn_unb_var1(U,B)_unb( FLA_Obj B, FLA_Obj U )
{
  FLA_Obj BT,              B0,
          BB,              b1t,
                           B2;

  FLA_Obj UTL,   UTR,      U00,  u01,       U02, 
          UBL,   UBR,      u10t, upsilon11, u12t,
                           U20,  u21,       U22;

  FLA_Part_2x1( B,    &BT, 
                      &BB,            0, FLA_TOP );

  FLA_Part_2x2( U,    &UTL, &UTR,
                      &UBL, &UBR,     0, 0, FLA_TR );

  while ( FLA_Obj_length( BT ) < FLA_Obj_length( B ) ){

    FLA_Repart_2x1_to_3x1( BT,                &B0, 
                        /* ** */            /* *** */
                                              &b1t, 
                           BB,                &B2,        1, FLA_BOTTOM );

    FLA_Repart_2x2_to_3x3( UTL, /**/ UTR,       &U00,  &u01,       /**/ &U02,
                        /* ************* */   /* **************************** */
                                                &u10t, &upsilon11, /**/ &u12t,
                           UBL, /**/ UBR,       &U20,  &u21,       /**/ &U22,
                           1, 1, FLA_BL );

    /*------------------------------------------------------------*/

    /*                       update line 1                        */
    /*                             :                              */
    /*                       update line n                        */

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x1_to_2x1( &BT,                B0, 
                                                  b1t, 
                            /* ** */           /* *** */
                              &BB,                B2,     FLA_TOP );

    FLA_Cont_with_3x3_to_2x2( &UTL, /**/ &UTR,       U00,  /**/ u01,       U02,
                                                     u10t, /**/ upsilon11, u12t,
                            /* ************** */  /* ************************** */
                              &UBL, /**/ &UBR,       U20,  /**/ u21,       U22,
                              FLA_TR );

  }

  return FLA_SUCCESS;
}

