/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 21 December 2012
 * Purpose: To provide a FileStream for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\FileStream.h
 */

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

class FileStream {
	public:
		FileStream(std::string filename, std::ios_base::openmode mode);
		bool OpenFile();
		bool CloseFile();
		bool ClearFile();
		bool CheckFileExists();
		bool ReadString(std::string& returnData);
		bool WriteString(std::string& writeData);
		bool ReadInt(int& returnData);
		bool WriteInt(int& writeData);
		bool ReadFloat(float& returnData);
		bool WriteFloat(float& writeData);
		void SetMode(std::ios_base::openmode mode);
	private:
		std::fstream mFileStream;
		std::string mName;
		std::ios_base::openmode mFlags;
};