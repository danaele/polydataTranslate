#include "PolydataTranslate.h"

/*polydataTranslate program*/

vtkSmartPointer <vtkPolyData> ReadVTKFile ( std::string vtkFile )
{
    // ReadFile vtkFile
    vtkSmartPointer <vtkPolyDataReader> reader = vtkSmartPointer <vtkPolyDataReader>::New() ;
    vtkSmartPointer <vtkPolyData> polyData = vtkSmartPointer <vtkPolyData>::New() ;
    reader->SetFileName( vtkFile.c_str() ) ;
    reader->OpenVTKFile() ;
    reader->Update() ;
    polyData = reader->GetOutput() ;
    //Checked if surface file with color no containing errors
    if ( reader->GetErrorCode() != 0 )
    {
        std::cout<<reader->GetErrorCode()<<std::endl;
        std::cerr << "Unable to open input file: " << vtkFile.c_str() << std::endl ;
        return 0 ;
    }
    else
    {
        return polyData ;
    }
}

int main ( int argc, char *argv[] )
{
    PARSE_ARGS ;
     // ReadFile vtkFile
    vtkSmartPointer <vtkPolyData> polyData = vtkSmartPointer <vtkPolyData>::New() ;
    polyData = ReadVTKFile(inputsurface) ;
    
    vtkSmartPointer<vtkTransform> translation =
    vtkSmartPointer<vtkTransform>::New();
    std::string hey = inputsurface ;
    
    translation->Translate(xtranslation,ytranslation,ztranslation);
    
    vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New(); 
    transformFilter->SetInputData(polyData); 
    transformFilter->SetTransform(translation); 
    transformFilter->Update();

     
     // Write the file
    vtkSmartPointer<vtkPolyDataWriter> writer = 
    vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetInputData(transformFilter->GetOutput());
    writer->SetFileName(outputsurface.c_str());
    writer->Write();
 
   
    std::cout << "Done !" << std::endl ;
    return EXIT_SUCCESS ;
}
