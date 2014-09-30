//=============================================================================
/*! clear all the matrix data and set the sizes 0 */
inline void zgematrix::clear()
{VERBOSE_REPORT;
  m =0;
  n =0;
  delete [] array;
  array =NULL;
  delete [] darray;
  darray =NULL;
}

//=============================================================================
/*! change the matrix into a zero matrix */
inline zgematrix& zgematrix::zero()
{VERBOSE_REPORT;
  for(long i=0; i<m*n; i++){
    array[i] =comple(0.0,0.0);
  }
  return *this;
}

//=============================================================================
/*! change the matrix into an identity matrix */
inline zgematrix& zgematrix::identity()
{VERBOSE_REPORT;
#ifdef  CPPL_DEBUG
  if(m!=n){
    ERROR_REPORT;
    std::cerr << "Only square matrix can be a identity matrix." << std::endl
              << "The matrix size was " << m << "x" << n << "." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  for(long i=0; i<m*n; i++){ array[i] =comple(0.0,0.0); }
  for(long i=0; i<m; i++){ operator()(i,i) =comple(1.0,0.0); }
  
  return *this;
}

//=============================================================================
/*! change sign(+/-) of the matrix */
inline void zgematrix::chsign()
{VERBOSE_REPORT;
  for(long i=0; i<m*n; i++){ array[i] =-array[i]; }
}

//=============================================================================
/*! make a deep copy of the matrix */
inline void zgematrix::copy(const zgematrix& mat)
{VERBOSE_REPORT;
  m =mat.m;
  n =mat.n;
  delete [] array;
  array =new comple[m*n];
  delete [] darray;
  darray =new comple*[n];
  for(int i=0; i<n; i++){ darray[i] =&array[i*m]; }

  zcopy_(mat.m*mat.n, mat.array, 1, array, 1);
}

//=============================================================================
/*! make a shallow copy of the matrix\n
  This function is not designed to be used in project codes. */
inline void zgematrix::shallow_copy(const _zgematrix& mat)
{VERBOSE_REPORT;
  m =mat.m;
  n =mat.n;
  delete [] array;
  array =mat.array;
  delete [] darray;
  darray =mat.darray;
  
  mat.nullify();
}

//=============================================================================
/*! resize the matrix */
inline void zgematrix::resize(const long& _m, const long& _n)
{VERBOSE_REPORT;
#ifdef  CPPL_DEBUG
  if( _m<0 || _n<0 ){
    ERROR_REPORT;
    std::cerr << "Matrix sizes must be positive integers." << std::endl
              << "Your input was (" << _m << "," << _n << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  m =_m;
  n =_n;
  delete [] array;
  array =new comple[m*n];
  delete [] darray;
  darray =new comple*[n];
  for(int i=0; i<n; i++){ darray[i] =&array[i*m]; }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! get row of the matrix */
inline _zrovector zgematrix::row(const long& _m) const
{VERBOSE_REPORT;
#ifdef  CPPL_DEBUG
  if( _m<0 || _m>m ){
    ERROR_REPORT;
    std::cerr << "Input row number must be between 0 and " << m << "." << std::endl
              << "Your input was " << _m << "." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zrovector v(n);
  for(long j=0; j<n; j++){ v(j)=(*this)(_m,j); }
  return _(v);
}

//=============================================================================
/*! get column of the matrix */
inline _zcovector zgematrix::col(const long& _n) const
{VERBOSE_REPORT;
#ifdef  CPPL_DEBUG
  if( _n<0 || _n>n ){
    ERROR_REPORT;
    std::cerr << "Input row number must be between 0 and " << n << "." << std::endl
              << "Your input was " << _n << "." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zcovector v(m);
  for(long i=0; i<m; i++){ v(i)=(*this)(i,_n); }
  return _(v);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! swap two matrices */
inline void swap(zgematrix& A, zgematrix& B)
{VERBOSE_REPORT;
  long A_m(A.m), A_n(A.n);
  comple* A_array(A.array);
  //comple** A_darray(A.darray);
  comple** A_darray=A.darray; //corruption to support VC++
  A.m=B.m; A.n=B.n; A.array=B.array; A.darray=B.darray;
  B.m=A_m; B.n=A_n; B.array=A_array; B.darray=A_darray;
}

//=============================================================================
/*! convert user object to smart-temporary object */
inline _zgematrix _(zgematrix& mat)
{VERBOSE_REPORT;
  _zgematrix newmat;

  //////// shallow copy ////////
  newmat.m =mat.m;
  newmat.n =mat.n;
  newmat.array =mat.array;
  newmat.darray =mat.darray;
  
  //////// nullify ////////
  mat.m =0;
  mat.n =0;
  mat.array =NULL;
  mat.darray =NULL;

  return newmat;
}
