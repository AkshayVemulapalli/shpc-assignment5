#include <stdio.h>
#include <math.h>
#include <time.h>

#include "FLAME.h"

#define TRUE 1
#define FALSE 0

void syrk_ln_blk_var1( FLA_Obj, FLA_Obj, int block_size );

int main(int argc, char *argv[])
{
    int n, nfirst, nlast, ninc, i, irep, nrepeats;

    double
        dtime, dtime_best, 
        diff;

    dtime_best = 0.0;

    FLA_Obj
        A, C, Cold, Cref;

    /* Initialize FLAME. */
    FLA_Init();

    printf( "%% number of repeats: " );
    scanf( "%d", &nrepeats );
    printf( "%% %d\n", nrepeats );

    printf( "%% enter nfirst, nlast, ninc: " );
    scanf( "%d%d%d", &nfirst, &nlast, &ninc );
    printf( "%% %d %d %d \n", nfirst, nlast, ninc );
    fflush( stdout );

    i = 1;
    for ( n=nfirst; n<= nlast; n+=ninc ) {

        // Create matrices
        FLA_Obj_create( FLA_DOUBLE, n, n, 1, n, &A );
        FLA_Obj_create( FLA_DOUBLE, n, n, 1, n, &C );
        FLA_Obj_create( FLA_DOUBLE, n, n, 1, n, &Cold );
        FLA_Obj_create( FLA_DOUBLE, n, n, 1, n, &Cref );


        FLA_Random_matrix( A );
        FLA_Random_matrix( Cold );

        for ( irep=0; irep<nrepeats; irep++ ) {
            FLA_Copy( Cold, Cref );

            dtime = FLA_Clock();

            // Reference SYRK call: Cref := A * Aᵀ + Cref
            FLA_Syrk( FLA_LOWER_TRIANGULAR, FLA_NO_TRANSPOSE, FLA_ONE, A, FLA_ONE, Cref );

            dtime = FLA_Clock() - dtime;

            if ( irep == 0 ) 
                dtime_best = dtime;
            else
                dtime_best = ( dtime < dtime_best ? dtime : dtime_best );
        }

        printf( "data_ref( %d, 1:2 ) = [ %d %le ];\n", i, n, dtime_best );
        fflush( stdout );

        // Time your implementation
        for ( irep=0; irep<nrepeats; irep++ ) {
            FLA_Copy( Cold, C );

            dtime = FLA_Clock();

            // Custom implementation
            int block_size = 10;
            syrk_ln_blk_var1( A, C, block_size);

            dtime = FLA_Clock() - dtime;

            if ( irep == 0 ) 
                dtime_best = dtime;
            else
                dtime_best = ( dtime < dtime_best ? dtime : dtime_best );
        }

        diff = FLA_Max_elemwise_diff( C, Cref );

        printf( "data_unb_var1( %d, 1:3 ) = [ %d %le %le ];\n", i, n, dtime_best, diff );
        fflush( stdout );

        FLA_Obj_free( &A );
        FLA_Obj_free( &C );
        FLA_Obj_free( &Cref );
        FLA_Obj_free( &Cold );

        i++;
    }

    FLA_Finalize();
    return 0;
}
