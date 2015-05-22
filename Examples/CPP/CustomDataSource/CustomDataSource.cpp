/***************************************************************************************************

  Zyan Disassembler Engine
  Version 1.0

  Remarks         : Freeware, Copyright must be included

  Original Author : Florian Bernd
  Modifications   : Joel Höner

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

***************************************************************************************************/

#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <Zydis.hpp>

class ZydisStdinInput : public Zydis::BaseInput
{
private:
    std::vector<uint8_t> m_buffer;   
    uint32_t             m_position = 0;
    uint64_t             m_globalPosition = 0;
private:
    void gatherInput();
protected:
    uint8_t internalInputPeek() override;
    uint8_t internalInputNext() override;
public:
    bool isEndOfInput() const override;
    uint64_t getPosition() const override;
    bool setPosition(uint64_t position) override;
};

void ZydisStdinInput::gatherInput()
{
    if (m_position != m_buffer.size())
    {
        return;
    }
    std::vector<uint8_t> buffer;
    bool valid;
    do
    {
        valid = true;
        buffer.clear();
        std::string input;
        std::getline(std::cin, input);
        if (input.empty())
        {
            valid = false;
            continue;
        }
        std::istringstream ss(input);
        uint32_t x;
        do
        {
            ss >> std::hex >> x;
            if (ss.fail())
            {
                std::cout << std::endl << "# Error: Invalid hex input." << std::endl << std::endl;
                ss.ignore();
                valid = false;
                break;
            } 
            if (buffer.size() == buffer.capacity())
            {
                buffer.reserve(buffer.capacity() + 512);
            }
            if (x > 255)
            {
                std::cout << std::endl << "# Warning: 0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << x 
                    << " converted to uint8_t. Possible data loss." << std::endl << std::endl;
            }
            buffer.resize(buffer.size() + 1);
            buffer[buffer.size() - 1] = static_cast<uint8_t>(x);
        } while (!ss.eof());
    } while (!valid);
    m_buffer = buffer;
    m_position = 0;
}

uint8_t ZydisStdinInput::internalInputPeek()
{
    gatherInput();
    return m_buffer[m_position];
}

uint8_t ZydisStdinInput::internalInputNext()
{
    gatherInput();
    m_globalPosition++;
    return m_buffer[m_position++];
}

bool ZydisStdinInput::isEndOfInput() const
{
    return false;
}

uint64_t ZydisStdinInput::getPosition() const
{
    return m_globalPosition;
}

bool ZydisStdinInput::setPosition(uint64_t position)
{
    if (position > m_globalPosition)
    {
        return false;
    }
    int64_t delta = m_globalPosition - position;
    if (delta > m_position)
    {
        return false;
    }
    m_position = m_position - static_cast<int32_t>(delta);
    m_globalPosition = position;
    return true;
}

int main()
{
    Zydis::InstructionInfo info;
    Zydis::InstructionDecoder decoder;
    Zydis::IntelInstructionFormatter formatter;
    ZydisStdinInput input;

    decoder.setDisassemblerMode(Zydis::DisassemblerMode::M32BIT);
    decoder.setDataSource(&input);
    decoder.setInstructionPointer(0x00000000);

    while (decoder.decodeInstruction(info))
    {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << std::uppercase 
                    << info.instrAddress << " "; 
        if (info.flags & Zydis::IF_ERROR_MASK)
        {
            std::cout << "db " << std::setw(2) << static_cast<int>(info.data[0]) << std::endl;    
        } else
        {
            std::cout << formatter.formatInstruction(info) << std::endl;
        }
    }

    return 0;
}