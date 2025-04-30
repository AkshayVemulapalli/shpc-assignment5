
/* Copyright 2025 The University of Texas at Austin  
 
   For licensing information see
                  http://www.cs.utexas.edu/users/flame/license.html 

   Programmed by: Name of author
                  Email of author
                                                                     */

#include "FLAME.h"

int Syrk_ln(_A,_C_)_unb( FLA_Obj C, FLA_Obj A )
{
  FLA_Obj CTL,   CTR,      C00,  c01,     C02, 
          CBL,   CBR,      c10t, gamma11, c12t,
                           C20,  c21,     C22;

  FLA_Obj AT,              A0,
          AB,              a1t,
                           A2;

  FLA_Part_2x2( C,    &CTL, &CTR,
                      &CBL, &CBR,     0, 0, FLA_TR );

  FLA_Part_2x1( A,    &AT, 
                      &AB,            0, FLA_TOP );

  while ( FLA_Obj_length( CTR ) < FLA_Obj_length( C ) ){

    FLA_Repart_2x2_to_3x3( CTL, /**/ CTR,       &C00,  &c01,     /**/ &C02,
                        /* ************* */   /* ************************** */
                                                &c10t, &gamma11, /**/ &c12t,
                           CBL, /**/ CBR,       &C20,  &c21,     /**/ &C22,
                           1, 1, FLA_BL );

    FLA_Repart_2x1_to_3x1( AT,                &A0, 
                        /* ** */            /* *** */
                                              &a1t, 
                           AB,                &A2,        1, FLA_BOTTOM );

    /*------------------------------------------------------------*/

    /*                       update line 1                        */
    /*                             :                              */
    /*                       update line n                        */

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x3_to_2x2( &CTL, /**/ &CTR,       C00,  /**/ c01,     C02,
                                                     c10t, /**/ gamma11, c12t,
                            /* ************** */  /* ************************ */
                              &CBL, /**/ &CBR,       C20,  /**/ c21,     C22,
                              FLA_TR );

    FLA_Cont_with_3x1_to_2x1( &AT,                A0, 
                                                  a1t, 
                            /* ** */           /* *** */
                              &AB,                A2,     FLA_TOP );

  }

  return FLA_SUCCESS;
}

