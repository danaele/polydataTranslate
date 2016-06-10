#include <vtkSmartPointer.h>
#include <iostream>

#include "vtkTestFilter.h"


int main(int,char *[])
{
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0,0.0,0.0);

  vtkSmartPointer<vtkPolyData> inputPolyData = vtkSmartPointer<vtkPolyData>::New();
  inputPolyData->SetPoints(points);

  std::cout<<"Input points: "<<inputPolyData->GetNumberOfPoints()<<std::endl;

  vtkSmartPointer<vtkTestFilter> filter = vtkSmartPointer<vtkTestFilter>::New();
  filter->SetInputData(inputPolyData);
  filter->Update();

  vtkPolyData* outputPolyData = filter->GetOutput();

  std::cout<<"Output points : " <<outputPolyData->GetNumberOfPoints()<<std::endl;

  return EXIT_SUCCESS;
}
