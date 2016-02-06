/**
 * @file platform/opengl/OpenGLEffectSourceCodeReader.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/FileStream.h>
#include <core/Memory.h>
#include <core/String.h>
#include <core/Tokeniser.h>
#include <core/Types.h>
#include <core/Utility.h>
#include <core/Vector.h>
#include <graphics/EffectCode.h>
#include <graphics/EffectSourceCodeReader.h>

using namespace Core;
using namespace Graphics;

// Implementation

class EffectSourceCodeReader::Implementation
{
public:

	Implementation()
		: _activeShaderSource(nullptr) { }

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	EffectCode* readCode(FileStream& fileStream)
	{
		Vector<Char8> data(fileStream.fileSize());
		fileStream.read(reinterpret_cast<Uint8*>(data.data()), static_cast<Uint32>(data.size()));
		const String8 tokenStream(data.data(), data.size());
		Tokeniser tokeniser("\t\n!%&()*+,-./:;<=>?[]^{|}~");
		const TokenList& tokens = tokeniser.tokenise(tokenStream);

		Int32 indentation = 0;

		for(TokenList::const_iterator i = tokens.begin(), end = tokens.end(); i != end; ++i)
		{
			if(i->lexeme[0] == '{')
			{
				if(indentation > 0 && _activeShaderSource != nullptr)
					_activeShaderSource->append(i->lexeme);

				++indentation;
			}
			else if(i->lexeme[0] == '}')
			{
				--indentation;

				if(indentation == 0)
					_activeShaderSource = nullptr;
				else if(_activeShaderSource != nullptr)
					_activeShaderSource->append(i->lexeme);
			}
			else if(i->lexeme == "VertexShader")
			{
				_activeShaderSource = &_vertexShaderSource;
			}
			else if(i->lexeme == "FragmentShader")
			{
				_activeShaderSource = &_fragmentShaderSource;
			}
			else if(_activeShaderSource != nullptr)
			{
				_activeShaderSource->append(i->lexeme);
			}
		}

		return createCode();
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	Core::String8 _fragmentShaderSource;
	Core::String8 _vertexShaderSource;
	Core::String8* _activeShaderSource;

	EffectCode* createCode() const
	{
		EffectCode* code = DE_NEW(EffectCode)();
		const Uint8* shaderCode = reinterpret_cast<const Uint8*>(_vertexShaderSource.c_str());
		code->setVertexShaderCode(ByteList(shaderCode, shaderCode + _vertexShaderSource.length() + 1u));
		shaderCode = reinterpret_cast<const Uint8*>(_fragmentShaderSource.c_str());
		code->setFragmentShaderCode(ByteList(shaderCode, shaderCode + _fragmentShaderSource.length() + 1u));

		return code;
	}
};


// Graphics::EffectSourceCodeReader

// Public

EffectSourceCodeReader::EffectSourceCodeReader()
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)();
}

EffectSourceCodeReader::~EffectSourceCodeReader()
{
	DE_DELETE(_implementation, Implementation);
}

EffectCode* EffectSourceCodeReader::readCode(FileStream& fileStream) const
{
	return _implementation->readCode(fileStream);
}
