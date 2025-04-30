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
B = randi( [1,3], [m,n] );  % random n x m matrix
          % make the matrix lower triangular
 
% Create a random matrix C
C_temp = randi([-3, 3], [m, m]);

U = triu(C_temp);

%% 
% Check whether trmm_lunn_blk_var1(U, B) computes the same as U * B 

if ( isequal( trmm_lunn_blk_var1(U, B, 10), U * B ) )
    disp( 'All seems well' );
else
    disp( 'Trouble in paradise' )
end
