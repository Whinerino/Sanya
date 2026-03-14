#include "Class.h"
ComplexNumber operator+(const int &lhs,const ComplexNumber &rhs){ComplexNumber result(lhs+rhs.GetRe(),rhs.GetIm());return result;}
ComplexNumber operator-(const int &lhs,const ComplexNumber &rhs){ComplexNumber result(lhs-rhs.GetRe(),rhs.GetIm());return result;}
ComplexNumber operator*(const int &lhs,const ComplexNumber &rhs){ComplexNumber result(lhs*rhs.GetRe(),lhs*rhs.GetIm());return result;}
ComplexNumber operator+(const double &lhs,const ComplexNumber &rhs){ComplexNumber result(lhs+rhs.GetRe(),rhs.GetIm());return result;}
ComplexNumber operator-(const double &lhs,const ComplexNumber &rhs){ComplexNumber result(lhs-rhs.GetRe(),rhs.GetIm());return result;}
ComplexNumber operator*(const double &lhs,const ComplexNumber &rhs){ComplexNumber result(lhs*rhs.GetRe(),lhs*rhs.GetIm());return result;} 


void CComplexVector0::show(const char *sf)
{
 if(sf)
 {
  ofstream outputFile;
  if(!outputFile){cout<<"Error!";throw -1;}     
  outputFile.open(sf,ios::out|ios::app);
  outputFile<<"{\n";
  for(size_t i=0;i<n;i++)
  {
   double im=v[i].GetIm();
   double re=v[i].GetRe();		
   if(re>0||re<0)
   {
    if(im>0){outputFile<<re<<"+i"<<im<<endl;}
    else if(im<0){outputFile<<re<<"-i"<<-im<<endl;}
    else{outputFile<<re<<endl;}
   } 
   else
   { 
    if(im>0||im<0){outputFile<<"i"<<im<<endl;}
    else{outputFile<<0<<endl;}
   } 
  } 
  outputFile<<"}"<<endl;
  outputFile.close();
 }
}

void CComplexVector1::show(const char *sf)
{
 if(sf)
 {
  ofstream outputFile;
  if(!outputFile){cout<<"Error!";throw -1;}
  outputFile.open(sf,ios::out|ios::app);
  outputFile<<"{ ";
  for(size_t i=0;i<n;i++)
  {
   double im=v[i].GetIm(); 
   double re=v[i].GetRe();
   if(re>0||re<0)
   {
    if(im>0){outputFile<<re<<"+i"<<im<<", ";}
    else if(im<0){outputFile<<re<<"-i"<<-im<<", ";}
    else{outputFile<<re<<endl;}
   } 
   else
   { 
    if(im>0||im<0){outputFile<<"i"<<im<<", ";}
    else{outputFile<<0<<", ";}
   } 
  } 
  outputFile<<"}"<<endl;
  outputFile.close();
 }
}


CComplexVector1 operator+(const CComplexVector &lhs,const CComplexVector &rhs)
{
 if(lhs.n>rhs.n)
 {
  CComplexVector1 result(lhs.n);
  for(size_t i=0;i<rhs.n;i++){result.v[i]=lhs[i]+rhs[i];}	
  for(size_t i=rhs.n;i<lhs.n;i++){result.v[i]=lhs[i];}
  return result;
 }
 else
 {
  CComplexVector1 result(rhs.n);
  for(size_t i=0;i<lhs.n;i++){result.v[i]=lhs[i]+rhs[i];}	
  for(size_t i=lhs.n;i<rhs.n;i++){result.v[i]=rhs[i];}
  return result;
 }
}

CComplexVector1 operator-(const CComplexVector &lhs,const CComplexVector &rhs)
{
 if(lhs.n>rhs.n)
 {
  CComplexVector1 result(lhs.n);
  for(size_t i=0;i<rhs.n;i++){result.v[i]=lhs[i]-rhs[i];}	
  for(size_t i=rhs.n;i<lhs.n;i++){result.v[i]=lhs[i];}
  return result;
 }
 else
 {
  CComplexVector1 result(rhs.n);
  for(size_t i=0;i<lhs.n;i++){result.v[i]=lhs[i]-rhs[i];}	
  for(size_t i=lhs.n;i<rhs.n;i++){result.v[i]=(-1)*rhs[i];}
  return result;
 }
}

ComplexNumber operator*(const CComplexVector &lhs,CComplexVector &rhs)
{
 ComplexNumber result;
 rhs.Conjugation();
 if(lhs.n>rhs.n)
 {
  for(size_t i=0;i<rhs.n;i++){result=result+lhs[i]*rhs[i];}
 }
 else
 {
  for(size_t i=0;i<lhs.n;i++){result=result+lhs[i]*rhs[i];}
 }
 rhs.Conjugation();
 return result;
}


CComplexVector *CComplexVector::create(int Type,const ComplexNumber *b,const int &nn)
{
 CComplexVector *t;
 if(Type==1){t=new CComplexVector0(b,nn);return t;}
 else{t=new CComplexVector1(b,nn);return t;}
}


ostream &operator<<(ostream &stream,const ComplexNumber &number)
{
 double Im=number.GetIm();
 double Re=number.GetRe();
 if(Re>0||Re<0)
 {
  if(Im>0){stream<<Re<<"+"<<Im<<"i";}
  else if(Im<0){stream<<Re<<Im<<"i";}
  else{stream<<Re;}
 }
 else
 { 
  if(Im>0||Im<0){stream<<Im<<"i";}
  else{stream<<0;}
 } 	
 return stream;
}

istream &operator>>(istream &stream,ComplexNumber &number)
{
 double n1,n2; 
 char s,i;
 if(stream>>n1)
 {
  number.Re=n1;
  if(stream.peek()=='\n'){return stream;}
  if(stream>>s)
  {
   if(s=='i'){number.Im=1;}
   else if(s=='+')
   {
    if(stream>>n2 && stream>>i && i=='i'){number.Im=n2;}
    else if(stream>>i && i=='i'){number.Im=1;}
   }
   else if(s=='-')
   {
    if(stream>>n2 && stream>>i && i=='i'){number.Im=-n2;}
    else if(stream>>i && i=='i'){number.Im=-1;}
   }
  }
  else{number.Im=0;}
 }
 else
 {
  if(stream>>s)
  {
   number.Re=0;
   if(s=='i'){number.Im=1;}
   if(s=='-')
   {
    if(stream>>n2){number.Im=n2;}
    else{number.Im=-1;}
   }
  }
 }
 return stream;
} 

