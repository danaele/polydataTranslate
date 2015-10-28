#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkDataReader.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkThreshold.h>
#include <vtkThresholdPoints.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGrid.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vtkPointData.h>
#include <list>
#include <map>
#include <iterator>
#include <ExtractLabelSurfacesCLP.h>

#include <vtksys/SystemTools.hxx> // for MakeDirectory()

int ExtractPointData(std::string vtkLabelFile, std::string labelNameInfo, std::string arrayName) ;
int TranslateToLabelNumber(std::string labelNameInfo, std::string labelNumberInfo) ;
int CreateSurfaceLabelFiles(std::string vtkFile, std::string labelNumberInfo, std::string prefix) ;
vtkSmartPointer<vtkPolyData> ReadVTKFile(std::string vtkFile) ;
