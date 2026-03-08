//
// Created by rchang on 3/4/26.
//

#include "Packet.h"

std::string Packet::decode(std::istringstream& stream)
{
    std::ostringstream stream_out;

    char c;
    char c_last = '\0';
    while (stream.get(c))
    {
        if (c_last == '\\')
        {
            if (c == '\\')
                stream_out << '\\';
            else if (c == 'n')
                stream_out << '\n';
        }
        else if (c == '\n')
        {
            break;
        }
        else
        {
            stream_out << c;
        }

        c_last = c;
    }

    return stream_out.str();
}

Packet::Packet(std::istringstream& stream)
{
}

void Packet::encode(const std::string& line, std::ostringstream& stream)
{
    for (const char c : line)
    {
        if (c == '\\')
            stream << "\\\\";
        else if (c == '\n')
            stream << "\\n";
        else
            stream << c;
    }
    stream << std::endl;
}

void Packet::serialize(std::ostringstream& stream)
{
    encode(prefix(), stream);
}
