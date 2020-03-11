/***
    This file is part of snapcast
    Copyright (C) 2014-2020  Johannes Pohl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef MESSAGE_FACTORY_HPP
#define MESSAGE_FACTORY_HPP

#include "codec_header.hpp"
#include "hello.hpp"
#include "server_settings.hpp"
#include "stream_tags.hpp"
#include "time.hpp"
#include "wire_chunk.hpp"

#include "common/str_compat.hpp"
#include "common/utils.hpp"
#include "json_message.hpp"
#include <string>


namespace msg
{
namespace factory
{

template <typename T>
static std::unique_ptr<T> createMessage(const BaseMessage& base_message, char* buffer)
{
    std::unique_ptr<T> result = std::make_unique<T>();
    if (!result)
        return nullptr;
    result->deserialize(base_message, buffer);
    return result;
}


static std::unique_ptr<BaseMessage> createMessage(const BaseMessage& base_message, char* buffer)
{
    std::unique_ptr<BaseMessage> result;
    switch (base_message.type)
    {
        case kCodecHeader:
            return createMessage<CodecHeader>(base_message, buffer);
        case kHello:
            return createMessage<Hello>(base_message, buffer);
        case kServerSettings:
            return createMessage<ServerSettings>(base_message, buffer);
        case kStreamTags:
            return createMessage<StreamTags>(base_message, buffer);
        case kTime:
            return createMessage<Time>(base_message, buffer);
        case kWireChunk:
            return createMessage<WireChunk>(base_message, buffer);
        default:
            return nullptr;
    }
}


} // namespace factory
} // namespace msg

#endif
