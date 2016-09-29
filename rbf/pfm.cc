#include "pfm.h"
#include <iostream>

// check if file already exists
bool fileExists(std::string fileName)
{
    std::fstream fs(fileName, std::ios::in);
    return fs.is_open();
}


PagedFileManager* PagedFileManager::_pf_manager = 0;

PagedFileManager* PagedFileManager::instance()
{
    if(!_pf_manager)
        _pf_manager = new PagedFileManager();

    return _pf_manager;
}


PagedFileManager::PagedFileManager()
{
}


PagedFileManager::~PagedFileManager()
{
}


RC PagedFileManager::createFile(const string &fileName)
{
    // return error if file already exists
    if(fileExists(fileName))
        return -1;

    // create file
    std::fstream fs(fileName, std::ios::in);
    fs.open(fileName, std::ios::out);
    //printf("Return Value: %d\n", fs.good() - 1);
    return fs.good() - 1;
}


RC PagedFileManager::destroyFile(const string &fileName)
{
    return std::remove(fileName.c_str());
}


RC PagedFileManager::openFile(const string &fileName, FileHandle &fileHandle)
{
    if(!fileExists(fileName))
    {
        printf("File did not Exist ...\n");
        return -1;
    }

    RC ret = fileHandle.openFile(fileName);
    printf("Return Value: %d\n", ret);
    return ret;
}


RC PagedFileManager::closeFile(FileHandle &fileHandle)
{
    RC ret = fileHandle.closeFile();
    std::cout  << "Return Code: " << ret <<endl;
    return ret;
}


FileHandle::FileHandle()
{
    readPageCounter = 0;
    writePageCounter = 0;
    appendPageCounter = 0;
    numberOfPages = 0;
}


FileHandle::~FileHandle()
{
}


RC FileHandle::readPage(PageNum pageNum, void *data)
{
    stream.seekg(PAGE_SIZE * (pageNum));
    stream.read(reinterpret_cast<char*>(data), PAGE_SIZE);
    readPageCounter++;

    return stream.good()-1;
}


RC FileHandle::writePage(PageNum pageNum, const void *data)
{
    stream.seekg(PAGE_SIZE * (pageNum));
    stream.read((char*)data, PAGE_SIZE);
    writePageCounter++;

    return stream.good()-1;
}


RC FileHandle::appendPage(const void *data)
{
    numberOfPages++;
    appendPageCounter++;
    stream.seekp(0,std::ios_base::end);
    stream.write((char*)data,PAGE_SIZE);

    return stream.good()-1;
}


unsigned FileHandle::getNumberOfPages()
{
    return numberOfPages;
}


RC FileHandle::collectCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount)
{
    readPageCount = readPageCounter;
    writePageCount = writePageCounter;
    appendPageCount = appendPageCounter;
    return 0;
}

RC FileHandle::openFile(std::string fileName)
{
    // check that no stream is currently associated with the fstream
     if(stream.is_open())
     {
         printf("The stream was already open!!!\n\n");
         return -1;
     }

     stream.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
     stream.seekg(0, ios::end);
     numberOfPages = stream.tellg()/PAGE_SIZE;
     stream.seekg(0, ios::beg);
     return stream.is_open() -1;//stream.good() - 1;
}

RC FileHandle::closeFile()
{
    if(stream.is_open())
    {
       stream.close();
       return !stream.is_open() - 1;//stream.good() - 1;
    }

    return -1;
}
