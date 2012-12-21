/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 21 December 2012
 * Purpose: To provide a FileStream for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\FileStream.cpp
 */

#include "FileStream.h"

FileStream::FileStream(std::string filename, std::ios_base::openmode mode)
{
	
	this->mName = filename;
	this->mFlags = mode;
}

bool FileStream::OpenFile()
{
	if (this->mFileStream.is_open())
	{
		return true;
	}

	this->mFileStream.open(this->mName.c_str(), this->mFlags);

	if (this->mFileStream.is_open())
		return true;

	return false;
}

bool FileStream::CloseFile()
{
	if (this->mFileStream.is_open())
	{
		this->mFileStream.close();
		return true;
	}

	return false;
}

bool FileStream::ClearFile()
{
	bool fileWasOpen = false;
	if (this->mFileStream.is_open())
	{
		this->mFileStream.close();
		fileWasOpen = true;
	}

	bool success = remove(this->mName.c_str());
	this->mFileStream.open(this->mName, this->mFlags);

	if (!fileWasOpen)
	{
		this->mFileStream.close();
	}

	return success;
}

bool FileStream::CheckFileExists()
{
	struct stat buf;
	if (stat(this->mName.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

bool FileStream::ReadString(std::string& returnData)
{
	if (this->mFileStream.is_open())
	{
		this->mFileStream >> returnData;

		return true;
	}

	return false;
}

bool FileStream::WriteString(std::string& writeData)
{
	if (this->mFileStream.is_open())
	{
		this->mFileStream << writeData << " ";

		return true;
	}

	return false;
}

bool FileStream::ReadInt(int& returnData)
{
	if (this->mFileStream.is_open())
	{
		this->mFileStream >> returnData;

		return true;
	}

	return false;
}

bool FileStream::WriteInt(int& writeData)
{
	if (this->mFileStream.is_open())
	{
		this->mFileStream << writeData << " ";

		return true;
	}

	return false;
}

bool FileStream::ReadFloat(float& returnData)
{
	if (this->mFileStream.is_open())
	{
		this->mFileStream >> returnData;

		return true;
	}

	return false;
}

bool FileStream::WriteFloat(float& writeData)
{
	if (this->mFileStream.is_open())
	{
		this->mFileStream << writeData << " ";

		return true;
	}

	return false;
}

void FileStream::SetMode(std::ios_base::openmode mode)
{
	this->mFlags = mode;
}