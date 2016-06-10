#ifndef __vtkTestFilter_h
#define __vtkTestFilter_h

#include "vtkPolyDataAlgorithm.h"

class vtkTestFilter : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTestFilter,vtkPolyDataAlgorithm);
  void PrintSelf(ostream &os, vtkIndent indent);

  static vtkTestFilter *New();

protected:
  vtkTestFilter();
//  ~vtkTestFilter();

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
  vtkTestFilter(const vtkTestFilter&);
  void operator =(const vtkTestFilter&);

};

#endif