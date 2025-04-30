% Set the path
% Creating character vector containing a search path that includes all the 
% folders and subfolders in libflameatlab
pathstoadd = genpath('../../libflameatlab');

addpath(pathstoadd);

%% 
% Setting the matrix dimension

m = 6;              % problem sizes
n = 4;
%% 

% Setting up a triangular matrix
L = randi( [1,3], [m,n] );  % random m x m matrix
            % make the matrix lower triangular
 
% Create a random matrix B

C_temp = randi([-3, 3], [m, m]);

C = tril(C_temp) + tril(C_temp,-1)';
C = tril(C);

%% 
% Check whether trmm_llnn_unb_var1( L, B ) computes the same as L*(L.') + C

if ( isequal( syrk_ln_unb_var1(L, C), tril(L*(L.') + C) ) )
    disp( 'All seems well' );
else
    disp( 'Trouble in paradise' )
end
