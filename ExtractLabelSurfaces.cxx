#include "ExtractLabelSurfaces.h"

int ExtractPointData(std::string vtkLabelFile, std::string labelNameInfo, std::string arrayName)
{
    std::cout<<" Start ExtractPointData..."<<std::endl;
    //Read VTK file
    vtkSmartPointer< vtkPolyData > polyData = vtkSmartPointer< vtkPolyData >::New() ;
    polyData = ReadVTKFile(vtkLabelFile);
    //Checked that array name specified exists in this vtk file
    vtkPointData* pointdata =  polyData->GetPointData();
    int arrayId=0;
    bool arrayFound=false;
    //Search all arrays in file
    for(unsigned i = 0; i < pointdata->GetNumberOfArrays(); i++)
    {
        if(pointdata->GetArrayName(i)==arrayName)
        {
            arrayId=i;
            arrayFound=true;
        }
    }
    if(arrayFound!=true)
    {
        std::cout<<"Array containing label specified not found"<<std::endl;
        return EXIT_FAILURE;
    }

    int arrayType = pointdata->GetArray(arrayId)->GetNumberOfComponents();
    std::cout<<"  Array name : "<<arrayName<<"\n  Number of components : "<<arrayType<<std::endl;
    //OutputFile
    std::ofstream outputFile;
    outputFile.open(labelNameInfo.c_str(),std::ofstream::out);
    if (outputFile.good())
    {
        outputFile << "#Text file containing label name information for each point - output of ExtractPointData tool \n";

        //Write in the file all labels corresponding to each points - in the same order
        for(vtkIdType j = 0; j < polyData->GetNumberOfPoints(); j++)
        {
            double vec[arrayType];  //search type
            pointdata->GetArray(arrayId)->GetTuple(j,vec);
            for(int k = 0 ; k < arrayType; k++)
            {
                outputFile << vec[k] <<" ";
            }
            outputFile <<"\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Unable to open file"<<std::endl;
        return EXIT_FAILURE;
    }
    std::cout<<" ExtractPointData Done !\n"<<std::endl;
    return EXIT_SUCCESS;
}

int TranslateToLabelNumber(std::string labelNameInfo, std::string labelNumberInfo)
{
    std::cout<<" Start TranslateToLabelNumber..."<<std::endl;

    std::ifstream inputFile;
    inputFile.open(labelNameInfo.c_str(), std::ios::in);
    std::ofstream outputFile;
    outputFile.open(labelNumberInfo.c_str() , std::ios::out);
    std::ofstream logFile;
    logFile.open("logLabelTable" , std::ios::out);

    std::string labelLine;
    //Define map containing labels and a list of points associated to them
    std::map<std::string, int> labelMap;
    //Map iterator
    std::map< std::string , int >::const_iterator mit,mend;
    int labelNumber=0;
    //Extract labels and points associated
    if(inputFile.good()) //file can be open
    {
        if(outputFile.good())
        {
            outputFile << "#Text file containing label number information for each point - output of TranslateToLabelNumber tool \n";
            getline(inputFile,labelLine); //format line
            getline(inputFile,labelLine);    //first labelName
            do
            {
                std::string newlabel=labelLine;
                if(labelMap.find(labelLine)!=labelMap.end())
                {
                    outputFile << labelMap[newlabel]<<"\n";
                }
                else
                {
                    labelNumber++;
                    labelMap[newlabel]=labelNumber;
                    outputFile << labelMap[newlabel]<<"\n";
                }
                getline(inputFile,labelLine);
            }while(!inputFile.eof());

        }
        else
        {
            std::cout<<"Cannot open  outputfile "<< labelNumberInfo<< std::endl;
            return EXIT_FAILURE;
        }
        outputFile.close();
    }
    else
    {
        std::cout<<"Cannot open the inputfile "<<std::endl;
        return EXIT_FAILURE;
    }
    //Write matching table between labels names and labels numbers
    if(logFile.good())
    {
        logFile << "Matching table between labels names and labels numbers \n";
        for(mit=labelMap.begin(),mend=labelMap.end();mit!=mend;++mit)
        {
            logFile << mit->first << " : "<< mit->second << "\n";
        }
    }
    else
    {
        std::cout<<"Cannot open logFile"<< labelNumberInfo<< std::endl;
        return EXIT_FAILURE;
    }
    logFile.close();
    std::cout<<"  Number of labels : "<<labelNumber<<std::endl;
    std::cout<<" TranslateToLabelNumber Done !\n"<<std::endl;
    return EXIT_SUCCESS;
}

int CreateSurfaceLabelFiles(std::string vtkFile, std::string labelNumberInfo)
{
    std::cout<<" Start CreateSurfaceLabelFiles..."<<std::endl;
    //Read labelInformation file
    std::ifstream inputFile;
    inputFile.open(labelNumberInfo.c_str(), std::ios::in);
    std::string labelLine;
    int nbLinesLabels=0;
    //Count number of label informations and checked if file can be open
    if(inputFile.good())
    {
        getline(inputFile,labelLine); //get information line
        do
        {
            getline(inputFile,labelLine);
            if(!labelLine.empty())
            {
                nbLinesLabels++;
            }
        }while(!inputFile.eof());
    }
    else
    {
        std::cout<<"Cannot open the label file "<<std::endl;
        return EXIT_FAILURE;
    }
    inputFile.close();

    // ReadFile vtkFile
    vtkSmartPointer< vtkPolyData > polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData = ReadVTKFile(vtkFile);

    int nbPoints=0;
    nbPoints=polyData->GetNumberOfPoints();
    //Check nb point vtkFile = nb point labelNumber
    if(nbPoints!=nbLinesLabels)
    {
        std::cout<<"Number of points in the VTK file aren't match with the number of labels information in the text file"<<std::endl;
        return EXIT_FAILURE;
    }

    //Add new array in vtkFile containing labelId informations for each points
    inputFile.open(labelNumberInfo.c_str(), std::ios::in);
    vtkSmartPointer<vtkIntArray> index = vtkSmartPointer<vtkIntArray>::New();
    index->SetNumberOfComponents(1);
    index->SetName("indexLabel");
    if(inputFile.good())
    {
        getline(inputFile,labelLine); //format line // Need to be checked
        //Create new array containing index label in the vtkFile

        for(int i=0 ; i < nbPoints ; i++)
        {
            getline(inputFile,labelLine); //format line // Need to be checked
            int valIndex = atoi(labelLine.c_str()) ;
            std::cout<<valIndex<<std::endl;
            index->InsertNextValue(valIndex);
        }
    }
    else
    {
        std::cout<<"Cannot open the label file "<<std::endl;
        return EXIT_FAILURE;
    }
    inputFile.close();
    polyData->GetPointData()->AddArray(index);
    //Create labels surfaces files
    //Define map containing labels and a list of points associated to them
    std::map< std::string , std::list<int> > labelMap;
    //Map iterator
    std::map< std::string , std::list<int> >::const_iterator mit,mend;
    //List iteration
    std::list<int>::const_iterator lit,lend;
    int idPoint=0; //point id

    //Extract labels and points associated
    if(inputFile.good())
    {
        getline(inputFile,labelLine); //format line // Need to be checked
        getline(inputFile,labelLine);    //first RGB value
        do
        {
            std::string newlabelRGB=labelLine;
            labelMap[newlabelRGB].push_back(idPoint);
            getline(inputFile,labelLine);
            idPoint++;
        }while(!inputFile.eof());
    }
    else
    {
        std::cout<<"Hello"<<std::endl;

        std::cout<<"Cannot open the label file "<<std::endl;
        return EXIT_FAILURE;
    }

    for(mit=labelMap.begin(),mend=labelMap.end();mit!=mend;++mit)
    {
        std::ofstream outputFile;
        std::string labelName = mit->first;

        //Rename label file to create
        replace(labelName.begin(),labelName.end(),' ','_');
        labelName += ".asc";

        //Write the ASCII file corresponding to one surface / one label
        outputFile.open(labelName.c_str() , std::ios::out);
        if(outputFile.good())
        {
            outputFile << "#!ascii - generated by CreateLabelFiles project \n";
            outputFile << mit->second.size() << " 0\n";
            for(lit=mit->second.begin(),lend=mit->second.end();lit!=lend;++lit)
            {
                double p[3];
                polyData->GetPoint(*lit,p);
                outputFile << p[0]<< " "<< p[1]<<" "<<p[2]<< " 0 \n";
            }
        }
        else
        {
            std::cout<<"Cannot open "<< labelName<< std::endl;
            return EXIT_FAILURE;
        }

        outputFile.close();
    }


    std::cout<<" CreateSurfaceLabelFiles Done !\n"<<std::endl;
    return EXIT_SUCCESS;
}

vtkSmartPointer<vtkPolyData> ReadVTKFile(std::string vtkFile)
{
    // ReadFile vtkFile
    vtkSmartPointer< vtkPolyDataReader > reader = vtkSmartPointer< vtkPolyDataReader >::New() ;
    vtkSmartPointer< vtkPolyData > polyData = vtkSmartPointer< vtkPolyData >::New() ;
    reader->SetFileName( vtkFile.c_str() ) ;
    reader->OpenVTKFile();
    reader->Update() ;
    polyData = reader->GetOutput() ;
    //Checked if surface file with color no containing errors
    if (reader->GetErrorCode() !=0 )
    {
        std::cerr << "Unable to open input file: " << vtkFile.c_str() << std::endl ;
        return 0;
    }
    else
    {
        return polyData;
    }
}


int main ( int argc, char *argv[] )
{
    PARSE_ARGS;

    if(extractPointData==0 && translateToLabelNumber==0 && createSurfaceLabelFiles==0 )
    {
        std::cout<<"Nothing to do. Specified at leat one action (--extractPointData or --translateToLabelNumber or --createSurfaceLabelFiles)"<<std::endl;
        return EXIT_FAILURE;
    }
    else if(extractPointData==1 && translateToLabelNumber==0 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run ExtractPointData tool ..."<<std::endl;
        if(!vtkLabelFile.empty() && !labelNameInfo.empty() && !arrayName.empty())
        {
            ExtractPointData(vtkLabelFile, labelNameInfo, arrayName);
        }
        else
        {
            std::cout<<"You need to specify --vtkLabelFile AND --arrayName AND --labelNameInfo "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==1 && translateToLabelNumber==1 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run ExtractPointData and TranslateToLabelNumber tools ..."<<std::endl;
        if(!vtkLabelFile.empty() && !labelNameInfo.empty() && !labelNumberInfo.empty() && !arrayName.empty())
        {
            ExtractPointData(vtkLabelFile, labelNameInfo, arrayName);
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --vtkLabelFile AND --arrayName AND --labelNameInfo AND --labelNumberInfo"<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==1 && translateToLabelNumber==1 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run ExtractPointData, TranslateToLabelNumber and CreateSurfaceLabelFiles tools ..."<<std::endl;
        if(!vtkLabelFile.empty() && !labelNameInfo.empty() && !labelNumberInfo.empty() && !vtkFile.empty() && !arrayName.empty())
        {
            ExtractPointData(vtkLabelFile, labelNameInfo, arrayName);
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
            CreateSurfaceLabelFiles(vtkFile, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --vtkLabelFile AND --arrayName AND --labelNameInfo AND --labelNumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==1 && createSurfaceLabelFiles==0)
    {
        std::cout<<"Run TranslateToLabelNumber tool ..."<<std::endl;
        if(!labelNameInfo.empty() && !labelNumberInfo.empty())
        {
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --labelNameInfo AND --labelNumberInfo"<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==1 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run TranslateToLabelNumber and CreateSurfaceLabelFiles tools ..."<<std::endl;
        if(!labelNameInfo.empty() && !labelNumberInfo.empty() && !vtkFile.empty())
        {
            TranslateToLabelNumber(labelNameInfo, labelNumberInfo);
            CreateSurfaceLabelFiles(vtkFile, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --labelNameInfo AND --labelNumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (extractPointData==0 && translateToLabelNumber==0 && createSurfaceLabelFiles==1)
    {
        std::cout<<"Run CreateSurfaceLabelFiles tool ..."<<std::endl;
        if(!labelNumberInfo.empty() && !vtkFile.empty())
        {
            CreateSurfaceLabelFiles(vtkFile, labelNumberInfo);
        }
        else
        {
            std::cout<<"You need to specify --labelNumberInfo AND --vtkFile "<<std::endl;
            return EXIT_FAILURE;
        }
    }
    else // case extractPointData==1 && translateToLabelNumber==0 && createSurfaceLabelFiles==1
    {
        std::cout<<"Wrong call";
        return EXIT_FAILURE;
    }
    std::cout<<"Done !"<<std::endl;
    return EXIT_SUCCESS ;
}
