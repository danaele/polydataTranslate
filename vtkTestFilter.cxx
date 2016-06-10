#include "vtkTestFilter.h"

#include "vtkObjectFactory.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformationVector.h"
#include "vtkInformation.h"
#include "vtkDataObject.h"
#include "vtkSmartPointer.h"


vtkStandardNewMacro(vtkTestFilter);

vtkTestFilter::vtkTestFilter()
{
  this->SetNumberOfInputPorts(1);
  this->SetNumberOfOutputPorts(1);
}

int vtkTestFilter::RequestData(vtkInformation *vtkNotUsed(request),
                           vtkInformationVector **inputVector,
                           vtkInformationVector *outputVector)
{
  //get input and output
  vtkPolyData* input =vtkPolyData::GetData(inputVector[0],0);
  vtkPolyData* output=vtkPolyData::GetData(outputVector,0);

  input->GetPoints()->InsertNextPoint(1.0,1.0,1.0);

  output->ShallowCopy(input);

  return 1;

}

void vtkTestFilter::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
