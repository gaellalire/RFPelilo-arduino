/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: rfpelilo.proto
 */

// This file is generated. Please do not edit!
#ifndef RFPELILO_H
#define RFPELILO_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <Defines.h>
#include <limits>

// Include external proto definitions

namespace rfpelilo {

enum class CommandStatus : uint32_t
{
  OK = 0,
  ERROR = 1,
  RF_FREQUENCY_ERROR = 2,
  RF_FREQUENCY_DEVIATION_ERROR = 3,
  RF_DATA_RATE_ERROR = 4,
  RF_PACKET_LENGTH_ERROR = 5,
  RF_TRANSMIT_FAILED = 6
};

class Empty final: public ::EmbeddedProto::MessageInterface
{
  public:
    Empty() = default;
    Empty(const Empty& rhs )
    {
    }

    Empty(const Empty&& rhs ) noexcept
    {
    }

    ~Empty() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
    };

    Empty& operator=(const Empty& rhs)
    {
      return *this;
    }

    Empty& operator=(const Empty&& rhs) noexcept
    {
      return *this;
    }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:



};

class ErrorMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    ErrorMessage() = default;
    ErrorMessage(const ErrorMessage& rhs )
    {
      set_text(rhs.get_text());
    }

    ErrorMessage(const ErrorMessage&& rhs ) noexcept
    {
      set_text(rhs.get_text());
    }

    ~ErrorMessage() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      TEXT = 1
    };

    ErrorMessage& operator=(const ErrorMessage& rhs)
    {
      set_text(rhs.get_text());
      return *this;
    }

    ErrorMessage& operator=(const ErrorMessage&& rhs) noexcept
    {
      set_text(rhs.get_text());
      return *this;
    }

    static constexpr char const* TEXT_NAME = "text";
    inline void clear_text() { text_.clear(); }
    inline ::EmbeddedProto::FieldString<200>& mutable_text() { return text_; }
    inline void set_text(const ::EmbeddedProto::FieldString<200>& rhs) { text_.set(rhs); }
    inline const ::EmbeddedProto::FieldString<200>& get_text() const { return text_; }
    inline const char* text() const { return text_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = text_.serialize_with_id(static_cast<uint32_t>(FieldNumber::TEXT), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::TEXT:
            return_value = text_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_text();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::TEXT:
          name = TEXT_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = text_.to_string(left_chars, indent_level + 2, TEXT_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      ::EmbeddedProto::FieldString<200> text_;

};

class ReceiveRFRequest final: public ::EmbeddedProto::MessageInterface
{
  public:
    ReceiveRFRequest() = default;
    ReceiveRFRequest(const ReceiveRFRequest& rhs )
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }

      set_dataRate(rhs.get_dataRate());
      set_bandwidth(rhs.get_bandwidth());
      set_rssiThreshold(rhs.get_rssiThreshold());
      set_maxMessageLength(rhs.get_maxMessageLength());
    }

    ReceiveRFRequest(const ReceiveRFRequest&& rhs ) noexcept
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }

      set_dataRate(rhs.get_dataRate());
      set_bandwidth(rhs.get_bandwidth());
      set_rssiThreshold(rhs.get_rssiThreshold());
      set_maxMessageLength(rhs.get_maxMessageLength());
    }

    ~ReceiveRFRequest() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MODULATION = 1,
      FREQUENCY = 2,
      DEVIATION = 3,
      DATARATE = 4,
      BANDWIDTH = 5,
      RSSITHRESHOLD = 6,
      MAXMESSAGELENGTH = 7
    };

    ReceiveRFRequest& operator=(const ReceiveRFRequest& rhs)
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }

      set_dataRate(rhs.get_dataRate());
      set_bandwidth(rhs.get_bandwidth());
      set_rssiThreshold(rhs.get_rssiThreshold());
      set_maxMessageLength(rhs.get_maxMessageLength());
      return *this;
    }

    ReceiveRFRequest& operator=(const ReceiveRFRequest&& rhs) noexcept
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }
      
      set_dataRate(rhs.get_dataRate());
      set_bandwidth(rhs.get_bandwidth());
      set_rssiThreshold(rhs.get_rssiThreshold());
      set_maxMessageLength(rhs.get_maxMessageLength());
      return *this;
    }

    static constexpr char const* MODULATION_NAME = "modulation";
    inline void clear_modulation() { modulation_.clear(); }
    inline void set_modulation(const uint32_t& value) { modulation_ = value; }
    inline void set_modulation(const uint32_t&& value) { modulation_ = value; }
    inline uint32_t& mutable_modulation() { return modulation_.get(); }
    inline const uint32_t& get_modulation() const { return modulation_.get(); }
    inline uint32_t modulation() const { return modulation_.get(); }

    static constexpr char const* FREQUENCY_NAME = "frequency";
    inline void clear_frequency() { frequency_.clear(); }
    inline void set_frequency(const float& value) { frequency_ = value; }
    inline void set_frequency(const float&& value) { frequency_ = value; }
    inline float& mutable_frequency() { return frequency_.get(); }
    inline const float& get_frequency() const { return frequency_.get(); }
    inline float frequency() const { return frequency_.get(); }

    static constexpr char const* DEVIATION_NAME = "deviation";
    inline bool has_deviation() const
    {
      return 0 != (presence::mask(presence::fields::DEVIATION) & presence_[presence::index(presence::fields::DEVIATION)]);
    }
    inline void clear_deviation()
    {
      presence_[presence::index(presence::fields::DEVIATION)] &= ~(presence::mask(presence::fields::DEVIATION));
      deviation_.clear();
    }
    inline void set_deviation(const float& value)
    {
      presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
      deviation_ = value;
    }
    inline void set_deviation(const float&& value)
    {
      presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
      deviation_ = value;
    }
    inline float& mutable_deviation()
    {
      presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
      return deviation_.get();
    }
    inline const float& get_deviation() const { return deviation_.get(); }
    inline float deviation() const { return deviation_.get(); }

    static constexpr char const* DATARATE_NAME = "dataRate";
    inline void clear_dataRate() { dataRate_.clear(); }
    inline void set_dataRate(const float& value) { dataRate_ = value; }
    inline void set_dataRate(const float&& value) { dataRate_ = value; }
    inline float& mutable_dataRate() { return dataRate_.get(); }
    inline const float& get_dataRate() const { return dataRate_.get(); }
    inline float dataRate() const { return dataRate_.get(); }

    static constexpr char const* BANDWIDTH_NAME = "bandwidth";
    inline void clear_bandwidth() { bandwidth_.clear(); }
    inline void set_bandwidth(const float& value) { bandwidth_ = value; }
    inline void set_bandwidth(const float&& value) { bandwidth_ = value; }
    inline float& mutable_bandwidth() { return bandwidth_.get(); }
    inline const float& get_bandwidth() const { return bandwidth_.get(); }
    inline float bandwidth() const { return bandwidth_.get(); }

    static constexpr char const* RSSITHRESHOLD_NAME = "rssiThreshold";
    inline void clear_rssiThreshold() { rssiThreshold_.clear(); }
    inline void set_rssiThreshold(const float& value) { rssiThreshold_ = value; }
    inline void set_rssiThreshold(const float&& value) { rssiThreshold_ = value; }
    inline float& mutable_rssiThreshold() { return rssiThreshold_.get(); }
    inline const float& get_rssiThreshold() const { return rssiThreshold_.get(); }
    inline float rssiThreshold() const { return rssiThreshold_.get(); }

    static constexpr char const* MAXMESSAGELENGTH_NAME = "maxMessageLength";
    inline void clear_maxMessageLength() { maxMessageLength_.clear(); }
    inline void set_maxMessageLength(const uint32_t& value) { maxMessageLength_ = value; }
    inline void set_maxMessageLength(const uint32_t&& value) { maxMessageLength_ = value; }
    inline uint32_t& mutable_maxMessageLength() { return maxMessageLength_.get(); }
    inline const uint32_t& get_maxMessageLength() const { return maxMessageLength_.get(); }
    inline uint32_t maxMessageLength() const { return maxMessageLength_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != modulation_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = modulation_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MODULATION), buffer, false);
      }

      if((0.0 != frequency_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = frequency_.serialize_with_id(static_cast<uint32_t>(FieldNumber::FREQUENCY), buffer, false);
      }

      if(has_deviation() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = deviation_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DEVIATION), buffer, true);
      }

      if((0.0 != dataRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = dataRate_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DATARATE), buffer, false);
      }

      if((0.0 != bandwidth_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = bandwidth_.serialize_with_id(static_cast<uint32_t>(FieldNumber::BANDWIDTH), buffer, false);
      }

      if((0.0 != rssiThreshold_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = rssiThreshold_.serialize_with_id(static_cast<uint32_t>(FieldNumber::RSSITHRESHOLD), buffer, false);
      }

      if((0U != maxMessageLength_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = maxMessageLength_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MAXMESSAGELENGTH), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::MODULATION:
            return_value = modulation_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::FREQUENCY:
            return_value = frequency_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DEVIATION:
            presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
            return_value = deviation_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DATARATE:
            return_value = dataRate_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::BANDWIDTH:
            return_value = bandwidth_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::RSSITHRESHOLD:
            return_value = rssiThreshold_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::MAXMESSAGELENGTH:
            return_value = maxMessageLength_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_modulation();
      clear_frequency();
      clear_deviation();
      clear_dataRate();
      clear_bandwidth();
      clear_rssiThreshold();
      clear_maxMessageLength();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::MODULATION:
          name = MODULATION_NAME;
          break;
        case FieldNumber::FREQUENCY:
          name = FREQUENCY_NAME;
          break;
        case FieldNumber::DEVIATION:
          name = DEVIATION_NAME;
          break;
        case FieldNumber::DATARATE:
          name = DATARATE_NAME;
          break;
        case FieldNumber::BANDWIDTH:
          name = BANDWIDTH_NAME;
          break;
        case FieldNumber::RSSITHRESHOLD:
          name = RSSITHRESHOLD_NAME;
          break;
        case FieldNumber::MAXMESSAGELENGTH:
          name = MAXMESSAGELENGTH_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = modulation_.to_string(left_chars, indent_level + 2, MODULATION_NAME, true);
      left_chars = frequency_.to_string(left_chars, indent_level + 2, FREQUENCY_NAME, false);
      left_chars = deviation_.to_string(left_chars, indent_level + 2, DEVIATION_NAME, false);
      left_chars = dataRate_.to_string(left_chars, indent_level + 2, DATARATE_NAME, false);
      left_chars = bandwidth_.to_string(left_chars, indent_level + 2, BANDWIDTH_NAME, false);
      left_chars = rssiThreshold_.to_string(left_chars, indent_level + 2, RSSITHRESHOLD_NAME, false);
      left_chars = maxMessageLength_.to_string(left_chars, indent_level + 2, MAXMESSAGELENGTH_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:

      // Define constants for tracking the presence of fields.
      // Use a struct to scope the variables from user fields as namespaces are not allowed within classes.
      struct presence
      {
        // An enumeration with all the fields for which presence has to be tracked.
        enum class fields : uint32_t
        {
          DEVIATION
        };

        // The number of fields for which presence has to be tracked.
        static constexpr uint32_t N_FIELDS = 1;

        // Which type are we using to track presence.
        using TYPE = uint32_t;

        // How many bits are there in the presence type.
        static constexpr uint32_t N_BITS = std::numeric_limits<TYPE>::digits;

        // How many variables of TYPE do we need to bit mask all presence fields.
        static constexpr uint32_t SIZE = (N_FIELDS / N_BITS) + ((N_FIELDS % N_BITS) > 0 ? 1 : 0);

        // Obtain the index of a given field in the presence array.
        static constexpr uint32_t index(const fields& field) { return static_cast<uint32_t>(field) / N_BITS; }

        // Obtain the bit mask for the given field assuming we are at the correct index in the presence array.
        static constexpr TYPE mask(const fields& field)
        {
          return static_cast<uint32_t>(0x01) << (static_cast<uint32_t>(field) % N_BITS);
        }
      };

      // Create an array in which the presence flags are stored.
      typename presence::TYPE presence_[presence::SIZE] = {0};

      EmbeddedProto::uint32 modulation_ = 0U;
      EmbeddedProto::floatfixed frequency_ = 0.0;
      EmbeddedProto::floatfixed deviation_ = 0.0;
      EmbeddedProto::floatfixed dataRate_ = 0.0;
      EmbeddedProto::floatfixed bandwidth_ = 0.0;
      EmbeddedProto::floatfixed rssiThreshold_ = 0.0;
      EmbeddedProto::uint32 maxMessageLength_ = 0U;

};

class ReceiveRFResponse final: public ::EmbeddedProto::MessageInterface
{
  public:
    ReceiveRFResponse() = default;
    ReceiveRFResponse(const ReceiveRFResponse& rhs )
    {
      set_data(rhs.get_data());
    }

    ReceiveRFResponse(const ReceiveRFResponse&& rhs ) noexcept
    {
      set_data(rhs.get_data());
    }

    ~ReceiveRFResponse() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      DATA = 1
    };

    ReceiveRFResponse& operator=(const ReceiveRFResponse& rhs)
    {
      set_data(rhs.get_data());
      return *this;
    }

    ReceiveRFResponse& operator=(const ReceiveRFResponse&& rhs) noexcept
    {
      set_data(rhs.get_data());
      return *this;
    }

    static constexpr char const* DATA_NAME = "data";
    inline void clear_data() { data_.clear(); }
    inline ::EmbeddedProto::FieldBytes<255>& mutable_data() { return data_; }
    inline void set_data(const ::EmbeddedProto::FieldBytes<255>& rhs) { data_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<255>& get_data() const { return data_; }
    inline const uint8_t* data() const { return data_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = data_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DATA), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::DATA:
            return_value = data_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_data();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::DATA:
          name = DATA_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = data_.to_string(left_chars, indent_level + 2, DATA_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      ::EmbeddedProto::FieldBytes<255> data_;

};

class SendRFRequest final: public ::EmbeddedProto::MessageInterface
{
  public:
    SendRFRequest() = default;
    SendRFRequest(const SendRFRequest& rhs )
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }

      set_dataRate(rhs.get_dataRate());
      set_data(rhs.get_data());
      if(rhs.has_repeat())
      {
        set_repeat(rhs.get_repeat());
      }
      else
      {
        clear_repeat();
      }

      if(rhs.has_repeatDelay())
      {
        set_repeatDelay(rhs.get_repeatDelay());
      }
      else
      {
        clear_repeatDelay();
      }

    }

    SendRFRequest(const SendRFRequest&& rhs ) noexcept
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }

      set_dataRate(rhs.get_dataRate());
      set_data(rhs.get_data());
      if(rhs.has_repeat())
      {
        set_repeat(rhs.get_repeat());
      }
      else
      {
        clear_repeat();
      }

      if(rhs.has_repeatDelay())
      {
        set_repeatDelay(rhs.get_repeatDelay());
      }
      else
      {
        clear_repeatDelay();
      }

    }

    ~SendRFRequest() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      MODULATION = 1,
      FREQUENCY = 2,
      DEVIATION = 3,
      DATARATE = 4,
      DATA = 5,
      REPEAT = 6,
      REPEATDELAY = 7
    };

    SendRFRequest& operator=(const SendRFRequest& rhs)
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }

      set_dataRate(rhs.get_dataRate());
      set_data(rhs.get_data());
      if(rhs.has_repeat())
      {
        set_repeat(rhs.get_repeat());
      }
      else
      {
        clear_repeat();
      }

      if(rhs.has_repeatDelay())
      {
        set_repeatDelay(rhs.get_repeatDelay());
      }
      else
      {
        clear_repeatDelay();
      }

      return *this;
    }

    SendRFRequest& operator=(const SendRFRequest&& rhs) noexcept
    {
      set_modulation(rhs.get_modulation());
      set_frequency(rhs.get_frequency());
      if(rhs.has_deviation())
      {
        set_deviation(rhs.get_deviation());
      }
      else
      {
        clear_deviation();
      }
      
      set_dataRate(rhs.get_dataRate());
      set_data(rhs.get_data());
      if(rhs.has_repeat())
      {
        set_repeat(rhs.get_repeat());
      }
      else
      {
        clear_repeat();
      }
      
      if(rhs.has_repeatDelay())
      {
        set_repeatDelay(rhs.get_repeatDelay());
      }
      else
      {
        clear_repeatDelay();
      }
      
      return *this;
    }

    static constexpr char const* MODULATION_NAME = "modulation";
    inline void clear_modulation() { modulation_.clear(); }
    inline void set_modulation(const uint32_t& value) { modulation_ = value; }
    inline void set_modulation(const uint32_t&& value) { modulation_ = value; }
    inline uint32_t& mutable_modulation() { return modulation_.get(); }
    inline const uint32_t& get_modulation() const { return modulation_.get(); }
    inline uint32_t modulation() const { return modulation_.get(); }

    static constexpr char const* FREQUENCY_NAME = "frequency";
    inline void clear_frequency() { frequency_.clear(); }
    inline void set_frequency(const float& value) { frequency_ = value; }
    inline void set_frequency(const float&& value) { frequency_ = value; }
    inline float& mutable_frequency() { return frequency_.get(); }
    inline const float& get_frequency() const { return frequency_.get(); }
    inline float frequency() const { return frequency_.get(); }

    static constexpr char const* DEVIATION_NAME = "deviation";
    inline bool has_deviation() const
    {
      return 0 != (presence::mask(presence::fields::DEVIATION) & presence_[presence::index(presence::fields::DEVIATION)]);
    }
    inline void clear_deviation()
    {
      presence_[presence::index(presence::fields::DEVIATION)] &= ~(presence::mask(presence::fields::DEVIATION));
      deviation_.clear();
    }
    inline void set_deviation(const float& value)
    {
      presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
      deviation_ = value;
    }
    inline void set_deviation(const float&& value)
    {
      presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
      deviation_ = value;
    }
    inline float& mutable_deviation()
    {
      presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
      return deviation_.get();
    }
    inline const float& get_deviation() const { return deviation_.get(); }
    inline float deviation() const { return deviation_.get(); }

    static constexpr char const* DATARATE_NAME = "dataRate";
    inline void clear_dataRate() { dataRate_.clear(); }
    inline void set_dataRate(const float& value) { dataRate_ = value; }
    inline void set_dataRate(const float&& value) { dataRate_ = value; }
    inline float& mutable_dataRate() { return dataRate_.get(); }
    inline const float& get_dataRate() const { return dataRate_.get(); }
    inline float dataRate() const { return dataRate_.get(); }

    static constexpr char const* DATA_NAME = "data";
    inline void clear_data() { data_.clear(); }
    inline ::EmbeddedProto::FieldBytes<255>& mutable_data() { return data_; }
    inline void set_data(const ::EmbeddedProto::FieldBytes<255>& rhs) { data_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<255>& get_data() const { return data_; }
    inline const uint8_t* data() const { return data_.get_const(); }

    static constexpr char const* REPEAT_NAME = "repeat";
    inline bool has_repeat() const
    {
      return 0 != (presence::mask(presence::fields::REPEAT) & presence_[presence::index(presence::fields::REPEAT)]);
    }
    inline void clear_repeat()
    {
      presence_[presence::index(presence::fields::REPEAT)] &= ~(presence::mask(presence::fields::REPEAT));
      repeat_.clear();
    }
    inline void set_repeat(const uint32_t& value)
    {
      presence_[presence::index(presence::fields::REPEAT)] |= presence::mask(presence::fields::REPEAT);
      repeat_ = value;
    }
    inline void set_repeat(const uint32_t&& value)
    {
      presence_[presence::index(presence::fields::REPEAT)] |= presence::mask(presence::fields::REPEAT);
      repeat_ = value;
    }
    inline uint32_t& mutable_repeat()
    {
      presence_[presence::index(presence::fields::REPEAT)] |= presence::mask(presence::fields::REPEAT);
      return repeat_.get();
    }
    inline const uint32_t& get_repeat() const { return repeat_.get(); }
    inline uint32_t repeat() const { return repeat_.get(); }

    static constexpr char const* REPEATDELAY_NAME = "repeatDelay";
    inline bool has_repeatDelay() const
    {
      return 0 != (presence::mask(presence::fields::REPEATDELAY) & presence_[presence::index(presence::fields::REPEATDELAY)]);
    }
    inline void clear_repeatDelay()
    {
      presence_[presence::index(presence::fields::REPEATDELAY)] &= ~(presence::mask(presence::fields::REPEATDELAY));
      repeatDelay_.clear();
    }
    inline void set_repeatDelay(const uint32_t& value)
    {
      presence_[presence::index(presence::fields::REPEATDELAY)] |= presence::mask(presence::fields::REPEATDELAY);
      repeatDelay_ = value;
    }
    inline void set_repeatDelay(const uint32_t&& value)
    {
      presence_[presence::index(presence::fields::REPEATDELAY)] |= presence::mask(presence::fields::REPEATDELAY);
      repeatDelay_ = value;
    }
    inline uint32_t& mutable_repeatDelay()
    {
      presence_[presence::index(presence::fields::REPEATDELAY)] |= presence::mask(presence::fields::REPEATDELAY);
      return repeatDelay_.get();
    }
    inline const uint32_t& get_repeatDelay() const { return repeatDelay_.get(); }
    inline uint32_t repeatDelay() const { return repeatDelay_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != modulation_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = modulation_.serialize_with_id(static_cast<uint32_t>(FieldNumber::MODULATION), buffer, false);
      }

      if((0.0 != frequency_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = frequency_.serialize_with_id(static_cast<uint32_t>(FieldNumber::FREQUENCY), buffer, false);
      }

      if(has_deviation() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = deviation_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DEVIATION), buffer, true);
      }

      if((0.0 != dataRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = dataRate_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DATARATE), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = data_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DATA), buffer, false);
      }

      if(has_repeat() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = repeat_.serialize_with_id(static_cast<uint32_t>(FieldNumber::REPEAT), buffer, true);
      }

      if(has_repeatDelay() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = repeatDelay_.serialize_with_id(static_cast<uint32_t>(FieldNumber::REPEATDELAY), buffer, true);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::MODULATION:
            return_value = modulation_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::FREQUENCY:
            return_value = frequency_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DEVIATION:
            presence_[presence::index(presence::fields::DEVIATION)] |= presence::mask(presence::fields::DEVIATION);
            return_value = deviation_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DATARATE:
            return_value = dataRate_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::DATA:
            return_value = data_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::REPEAT:
            presence_[presence::index(presence::fields::REPEAT)] |= presence::mask(presence::fields::REPEAT);
            return_value = repeat_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::REPEATDELAY:
            presence_[presence::index(presence::fields::REPEATDELAY)] |= presence::mask(presence::fields::REPEATDELAY);
            return_value = repeatDelay_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_modulation();
      clear_frequency();
      clear_deviation();
      clear_dataRate();
      clear_data();
      clear_repeat();
      clear_repeatDelay();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::MODULATION:
          name = MODULATION_NAME;
          break;
        case FieldNumber::FREQUENCY:
          name = FREQUENCY_NAME;
          break;
        case FieldNumber::DEVIATION:
          name = DEVIATION_NAME;
          break;
        case FieldNumber::DATARATE:
          name = DATARATE_NAME;
          break;
        case FieldNumber::DATA:
          name = DATA_NAME;
          break;
        case FieldNumber::REPEAT:
          name = REPEAT_NAME;
          break;
        case FieldNumber::REPEATDELAY:
          name = REPEATDELAY_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = modulation_.to_string(left_chars, indent_level + 2, MODULATION_NAME, true);
      left_chars = frequency_.to_string(left_chars, indent_level + 2, FREQUENCY_NAME, false);
      left_chars = deviation_.to_string(left_chars, indent_level + 2, DEVIATION_NAME, false);
      left_chars = dataRate_.to_string(left_chars, indent_level + 2, DATARATE_NAME, false);
      left_chars = data_.to_string(left_chars, indent_level + 2, DATA_NAME, false);
      left_chars = repeat_.to_string(left_chars, indent_level + 2, REPEAT_NAME, false);
      left_chars = repeatDelay_.to_string(left_chars, indent_level + 2, REPEATDELAY_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:

      // Define constants for tracking the presence of fields.
      // Use a struct to scope the variables from user fields as namespaces are not allowed within classes.
      struct presence
      {
        // An enumeration with all the fields for which presence has to be tracked.
        enum class fields : uint32_t
        {
          DEVIATION,
          REPEAT,
          REPEATDELAY
        };

        // The number of fields for which presence has to be tracked.
        static constexpr uint32_t N_FIELDS = 3;

        // Which type are we using to track presence.
        using TYPE = uint32_t;

        // How many bits are there in the presence type.
        static constexpr uint32_t N_BITS = std::numeric_limits<TYPE>::digits;

        // How many variables of TYPE do we need to bit mask all presence fields.
        static constexpr uint32_t SIZE = (N_FIELDS / N_BITS) + ((N_FIELDS % N_BITS) > 0 ? 1 : 0);

        // Obtain the index of a given field in the presence array.
        static constexpr uint32_t index(const fields& field) { return static_cast<uint32_t>(field) / N_BITS; }

        // Obtain the bit mask for the given field assuming we are at the correct index in the presence array.
        static constexpr TYPE mask(const fields& field)
        {
          return static_cast<uint32_t>(0x01) << (static_cast<uint32_t>(field) % N_BITS);
        }
      };

      // Create an array in which the presence flags are stored.
      typename presence::TYPE presence_[presence::SIZE] = {0};

      EmbeddedProto::uint32 modulation_ = 0U;
      EmbeddedProto::floatfixed frequency_ = 0.0;
      EmbeddedProto::floatfixed deviation_ = 0.0;
      EmbeddedProto::floatfixed dataRate_ = 0.0;
      ::EmbeddedProto::FieldBytes<255> data_;
      EmbeddedProto::uint32 repeat_ = 0U;
      EmbeddedProto::uint32 repeatDelay_ = 0U;

};

class Main final: public ::EmbeddedProto::MessageInterface
{
  public:
    Main() = default;
    Main(const Main& rhs )
    {
      set_command_id(rhs.get_command_id());
      set_command_status(rhs.get_command_status());
      set_has_next(rhs.get_has_next());
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::EMPTY:
          set_empty(rhs.get_empty());
          break;

        case FieldNumber::SEND_RF_REQUEST:
          set_send_rf_request(rhs.get_send_rf_request());
          break;

        case FieldNumber::ERROR_MESSAGE:
          set_error_message(rhs.get_error_message());
          break;

        case FieldNumber::RECEIVE_RF_REQUEST:
          set_receive_rf_request(rhs.get_receive_rf_request());
          break;

        case FieldNumber::RECEIVE_RF_RESPONSE:
          set_receive_rf_response(rhs.get_receive_rf_response());
          break;

        default:
          break;
      }

    }

    Main(const Main&& rhs ) noexcept
    {
      set_command_id(rhs.get_command_id());
      set_command_status(rhs.get_command_status());
      set_has_next(rhs.get_has_next());
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::EMPTY:
          set_empty(rhs.get_empty());
          break;

        case FieldNumber::SEND_RF_REQUEST:
          set_send_rf_request(rhs.get_send_rf_request());
          break;

        case FieldNumber::ERROR_MESSAGE:
          set_error_message(rhs.get_error_message());
          break;

        case FieldNumber::RECEIVE_RF_REQUEST:
          set_receive_rf_request(rhs.get_receive_rf_request());
          break;

        case FieldNumber::RECEIVE_RF_RESPONSE:
          set_receive_rf_response(rhs.get_receive_rf_response());
          break;

        default:
          break;
      }

    }

    ~Main() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      COMMAND_ID = 1,
      COMMAND_STATUS = 2,
      HAS_NEXT = 3,
      EMPTY = 4,
      SEND_RF_REQUEST = 5,
      ERROR_MESSAGE = 6,
      RECEIVE_RF_REQUEST = 7,
      RECEIVE_RF_RESPONSE = 8
    };

    Main& operator=(const Main& rhs)
    {
      set_command_id(rhs.get_command_id());
      set_command_status(rhs.get_command_status());
      set_has_next(rhs.get_has_next());
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::EMPTY:
          set_empty(rhs.get_empty());
          break;

        case FieldNumber::SEND_RF_REQUEST:
          set_send_rf_request(rhs.get_send_rf_request());
          break;

        case FieldNumber::ERROR_MESSAGE:
          set_error_message(rhs.get_error_message());
          break;

        case FieldNumber::RECEIVE_RF_REQUEST:
          set_receive_rf_request(rhs.get_receive_rf_request());
          break;

        case FieldNumber::RECEIVE_RF_RESPONSE:
          set_receive_rf_response(rhs.get_receive_rf_response());
          break;

        default:
          break;
      }

      return *this;
    }

    Main& operator=(const Main&& rhs) noexcept
    {
      set_command_id(rhs.get_command_id());
      set_command_status(rhs.get_command_status());
      set_has_next(rhs.get_has_next());
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::EMPTY:
          set_empty(rhs.get_empty());
          break;

        case FieldNumber::SEND_RF_REQUEST:
          set_send_rf_request(rhs.get_send_rf_request());
          break;

        case FieldNumber::ERROR_MESSAGE:
          set_error_message(rhs.get_error_message());
          break;

        case FieldNumber::RECEIVE_RF_REQUEST:
          set_receive_rf_request(rhs.get_receive_rf_request());
          break;

        case FieldNumber::RECEIVE_RF_RESPONSE:
          set_receive_rf_response(rhs.get_receive_rf_response());
          break;

        default:
          break;
      }

      return *this;
    }

    static constexpr char const* COMMAND_ID_NAME = "command_id";
    inline void clear_command_id() { command_id_.clear(); }
    inline void set_command_id(const uint32_t& value) { command_id_ = value; }
    inline void set_command_id(const uint32_t&& value) { command_id_ = value; }
    inline uint32_t& mutable_command_id() { return command_id_.get(); }
    inline const uint32_t& get_command_id() const { return command_id_.get(); }
    inline uint32_t command_id() const { return command_id_.get(); }

    static constexpr char const* COMMAND_STATUS_NAME = "command_status";
    inline void clear_command_status() { command_status_.clear(); }
    inline void set_command_status(const CommandStatus& value) { command_status_ = value; }
    inline void set_command_status(const CommandStatus&& value) { command_status_ = value; }
    inline const CommandStatus& get_command_status() const { return command_status_.get(); }
    inline CommandStatus command_status() const { return command_status_.get(); }

    static constexpr char const* HAS_NEXT_NAME = "has_next";
    inline void clear_has_next() { has_next_.clear(); }
    inline void set_has_next(const bool& value) { has_next_ = value; }
    inline void set_has_next(const bool&& value) { has_next_ = value; }
    inline bool& mutable_has_next() { return has_next_.get(); }
    inline const bool& get_has_next() const { return has_next_.get(); }
    inline bool has_next() const { return has_next_.get(); }

    FieldNumber get_which_content() const { return which_content_; }

    static constexpr char const* EMPTY_NAME = "empty";
    inline bool has_empty() const
    {
      return FieldNumber::EMPTY == which_content_;
    }
    inline void clear_empty()
    {
      if(FieldNumber::EMPTY == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.empty_.~Empty();
      }
    }
    inline void set_empty(const Empty& value)
    {
      if(FieldNumber::EMPTY != which_content_)
      {
        init_content(FieldNumber::EMPTY);
      }
      content_.empty_ = value;
    }
    inline void set_empty(const Empty&& value)
    {
      if(FieldNumber::EMPTY != which_content_)
      {
        init_content(FieldNumber::EMPTY);
      }
      content_.empty_ = value;
    }
    inline Empty& mutable_empty()
    {
      if(FieldNumber::EMPTY != which_content_)
      {
        init_content(FieldNumber::EMPTY);
      }
      return content_.empty_;
    }
    inline const Empty& get_empty() const { return content_.empty_; }
    inline const Empty& empty() const { return content_.empty_; }

    static constexpr char const* SEND_RF_REQUEST_NAME = "send_rf_request";
    inline bool has_send_rf_request() const
    {
      return FieldNumber::SEND_RF_REQUEST == which_content_;
    }
    inline void clear_send_rf_request()
    {
      if(FieldNumber::SEND_RF_REQUEST == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.send_rf_request_.~SendRFRequest();
      }
    }
    inline void set_send_rf_request(const SendRFRequest& value)
    {
      if(FieldNumber::SEND_RF_REQUEST != which_content_)
      {
        init_content(FieldNumber::SEND_RF_REQUEST);
      }
      content_.send_rf_request_ = value;
    }
    inline void set_send_rf_request(const SendRFRequest&& value)
    {
      if(FieldNumber::SEND_RF_REQUEST != which_content_)
      {
        init_content(FieldNumber::SEND_RF_REQUEST);
      }
      content_.send_rf_request_ = value;
    }
    inline SendRFRequest& mutable_send_rf_request()
    {
      if(FieldNumber::SEND_RF_REQUEST != which_content_)
      {
        init_content(FieldNumber::SEND_RF_REQUEST);
      }
      return content_.send_rf_request_;
    }
    inline const SendRFRequest& get_send_rf_request() const { return content_.send_rf_request_; }
    inline const SendRFRequest& send_rf_request() const { return content_.send_rf_request_; }

    static constexpr char const* ERROR_MESSAGE_NAME = "error_message";
    inline bool has_error_message() const
    {
      return FieldNumber::ERROR_MESSAGE == which_content_;
    }
    inline void clear_error_message()
    {
      if(FieldNumber::ERROR_MESSAGE == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.error_message_.~ErrorMessage();
      }
    }
    inline void set_error_message(const ErrorMessage& value)
    {
      if(FieldNumber::ERROR_MESSAGE != which_content_)
      {
        init_content(FieldNumber::ERROR_MESSAGE);
      }
      content_.error_message_ = value;
    }
    inline void set_error_message(const ErrorMessage&& value)
    {
      if(FieldNumber::ERROR_MESSAGE != which_content_)
      {
        init_content(FieldNumber::ERROR_MESSAGE);
      }
      content_.error_message_ = value;
    }
    inline ErrorMessage& mutable_error_message()
    {
      if(FieldNumber::ERROR_MESSAGE != which_content_)
      {
        init_content(FieldNumber::ERROR_MESSAGE);
      }
      return content_.error_message_;
    }
    inline const ErrorMessage& get_error_message() const { return content_.error_message_; }
    inline const ErrorMessage& error_message() const { return content_.error_message_; }

    static constexpr char const* RECEIVE_RF_REQUEST_NAME = "receive_rf_request";
    inline bool has_receive_rf_request() const
    {
      return FieldNumber::RECEIVE_RF_REQUEST == which_content_;
    }
    inline void clear_receive_rf_request()
    {
      if(FieldNumber::RECEIVE_RF_REQUEST == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.receive_rf_request_.~ReceiveRFRequest();
      }
    }
    inline void set_receive_rf_request(const ReceiveRFRequest& value)
    {
      if(FieldNumber::RECEIVE_RF_REQUEST != which_content_)
      {
        init_content(FieldNumber::RECEIVE_RF_REQUEST);
      }
      content_.receive_rf_request_ = value;
    }
    inline void set_receive_rf_request(const ReceiveRFRequest&& value)
    {
      if(FieldNumber::RECEIVE_RF_REQUEST != which_content_)
      {
        init_content(FieldNumber::RECEIVE_RF_REQUEST);
      }
      content_.receive_rf_request_ = value;
    }
    inline ReceiveRFRequest& mutable_receive_rf_request()
    {
      if(FieldNumber::RECEIVE_RF_REQUEST != which_content_)
      {
        init_content(FieldNumber::RECEIVE_RF_REQUEST);
      }
      return content_.receive_rf_request_;
    }
    inline const ReceiveRFRequest& get_receive_rf_request() const { return content_.receive_rf_request_; }
    inline const ReceiveRFRequest& receive_rf_request() const { return content_.receive_rf_request_; }

    static constexpr char const* RECEIVE_RF_RESPONSE_NAME = "receive_rf_response";
    inline bool has_receive_rf_response() const
    {
      return FieldNumber::RECEIVE_RF_RESPONSE == which_content_;
    }
    inline void clear_receive_rf_response()
    {
      if(FieldNumber::RECEIVE_RF_RESPONSE == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.receive_rf_response_.~ReceiveRFResponse();
      }
    }
    inline void set_receive_rf_response(const ReceiveRFResponse& value)
    {
      if(FieldNumber::RECEIVE_RF_RESPONSE != which_content_)
      {
        init_content(FieldNumber::RECEIVE_RF_RESPONSE);
      }
      content_.receive_rf_response_ = value;
    }
    inline void set_receive_rf_response(const ReceiveRFResponse&& value)
    {
      if(FieldNumber::RECEIVE_RF_RESPONSE != which_content_)
      {
        init_content(FieldNumber::RECEIVE_RF_RESPONSE);
      }
      content_.receive_rf_response_ = value;
    }
    inline ReceiveRFResponse& mutable_receive_rf_response()
    {
      if(FieldNumber::RECEIVE_RF_RESPONSE != which_content_)
      {
        init_content(FieldNumber::RECEIVE_RF_RESPONSE);
      }
      return content_.receive_rf_response_;
    }
    inline const ReceiveRFResponse& get_receive_rf_response() const { return content_.receive_rf_response_; }
    inline const ReceiveRFResponse& receive_rf_response() const { return content_.receive_rf_response_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != command_id_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = command_id_.serialize_with_id(static_cast<uint32_t>(FieldNumber::COMMAND_ID), buffer, false);
      }

      if((static_cast<CommandStatus>(0) != command_status_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = command_status_.serialize_with_id(static_cast<uint32_t>(FieldNumber::COMMAND_STATUS), buffer, false);
      }

      if((false != has_next_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = has_next_.serialize_with_id(static_cast<uint32_t>(FieldNumber::HAS_NEXT), buffer, false);
      }

      switch(which_content_)
      {
        case FieldNumber::EMPTY:
          if(has_empty() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.empty_.serialize_with_id(static_cast<uint32_t>(FieldNumber::EMPTY), buffer, true);
          }
          break;

        case FieldNumber::SEND_RF_REQUEST:
          if(has_send_rf_request() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.send_rf_request_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SEND_RF_REQUEST), buffer, true);
          }
          break;

        case FieldNumber::ERROR_MESSAGE:
          if(has_error_message() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.error_message_.serialize_with_id(static_cast<uint32_t>(FieldNumber::ERROR_MESSAGE), buffer, true);
          }
          break;

        case FieldNumber::RECEIVE_RF_REQUEST:
          if(has_receive_rf_request() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.receive_rf_request_.serialize_with_id(static_cast<uint32_t>(FieldNumber::RECEIVE_RF_REQUEST), buffer, true);
          }
          break;

        case FieldNumber::RECEIVE_RF_RESPONSE:
          if(has_receive_rf_response() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.receive_rf_response_.serialize_with_id(static_cast<uint32_t>(FieldNumber::RECEIVE_RF_RESPONSE), buffer, true);
          }
          break;

        default:
          break;
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::COMMAND_ID:
            return_value = command_id_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::COMMAND_STATUS:
            return_value = command_status_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::HAS_NEXT:
            return_value = has_next_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::EMPTY:
          case FieldNumber::SEND_RF_REQUEST:
          case FieldNumber::ERROR_MESSAGE:
          case FieldNumber::RECEIVE_RF_REQUEST:
          case FieldNumber::RECEIVE_RF_RESPONSE:
            return_value = deserialize_content(id_tag, buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_command_id();
      clear_command_status();
      clear_has_next();
      clear_content();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::COMMAND_ID:
          name = COMMAND_ID_NAME;
          break;
        case FieldNumber::COMMAND_STATUS:
          name = COMMAND_STATUS_NAME;
          break;
        case FieldNumber::HAS_NEXT:
          name = HAS_NEXT_NAME;
          break;
        case FieldNumber::EMPTY:
          name = EMPTY_NAME;
          break;
        case FieldNumber::SEND_RF_REQUEST:
          name = SEND_RF_REQUEST_NAME;
          break;
        case FieldNumber::ERROR_MESSAGE:
          name = ERROR_MESSAGE_NAME;
          break;
        case FieldNumber::RECEIVE_RF_REQUEST:
          name = RECEIVE_RF_REQUEST_NAME;
          break;
        case FieldNumber::RECEIVE_RF_RESPONSE:
          name = RECEIVE_RF_RESPONSE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = command_id_.to_string(left_chars, indent_level + 2, COMMAND_ID_NAME, true);
      left_chars = command_status_.to_string(left_chars, indent_level + 2, COMMAND_STATUS_NAME, false);
      left_chars = has_next_.to_string(left_chars, indent_level + 2, HAS_NEXT_NAME, false);
      left_chars = to_string_content(left_chars, indent_level + 2, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::uint32 command_id_ = 0U;
      EmbeddedProto::enumeration<CommandStatus> command_status_ = static_cast<CommandStatus>(0);
      EmbeddedProto::boolean has_next_ = false;

      FieldNumber which_content_ = FieldNumber::NOT_SET;
      union content
      {
        content() {}
        ~content() {}
        Empty empty_;
        SendRFRequest send_rf_request_;
        ErrorMessage error_message_;
        ReceiveRFRequest receive_rf_request_;
        ReceiveRFResponse receive_rf_response_;
      };
      content content_;

      void init_content(const FieldNumber field_id)
      {
        if(FieldNumber::NOT_SET != which_content_)
        {
          // First delete the old object in the oneof.
          clear_content();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case FieldNumber::EMPTY:
            new(&content_.empty_) Empty;
            break;

          case FieldNumber::SEND_RF_REQUEST:
            new(&content_.send_rf_request_) SendRFRequest;
            break;

          case FieldNumber::ERROR_MESSAGE:
            new(&content_.error_message_) ErrorMessage;
            break;

          case FieldNumber::RECEIVE_RF_REQUEST:
            new(&content_.receive_rf_request_) ReceiveRFRequest;
            break;

          case FieldNumber::RECEIVE_RF_RESPONSE:
            new(&content_.receive_rf_response_) ReceiveRFResponse;
            break;

          default:
            break;
         }

         which_content_ = field_id;
      }

      void clear_content()
      {
        switch(which_content_)
        {
          case FieldNumber::EMPTY:
            ::EmbeddedProto::destroy_at(&content_.empty_);
            break;
          case FieldNumber::SEND_RF_REQUEST:
            ::EmbeddedProto::destroy_at(&content_.send_rf_request_);
            break;
          case FieldNumber::ERROR_MESSAGE:
            ::EmbeddedProto::destroy_at(&content_.error_message_);
            break;
          case FieldNumber::RECEIVE_RF_REQUEST:
            ::EmbeddedProto::destroy_at(&content_.receive_rf_request_);
            break;
          case FieldNumber::RECEIVE_RF_RESPONSE:
            ::EmbeddedProto::destroy_at(&content_.receive_rf_response_);
            break;
          default:
            break;
        }
        which_content_ = FieldNumber::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_content(const FieldNumber field_id, 
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
        
        if(field_id != which_content_)
        {
          init_content(field_id);
        }

        switch(which_content_)
        {
          case FieldNumber::EMPTY:
            return_value = content_.empty_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::SEND_RF_REQUEST:
            return_value = content_.send_rf_request_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::ERROR_MESSAGE:
            return_value = content_.error_message_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::RECEIVE_RF_REQUEST:
            return_value = content_.receive_rf_request_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::RECEIVE_RF_RESPONSE:
            return_value = content_.receive_rf_response_.deserialize_check_type(buffer, wire_type);
            break;
          default:
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_content();
        }
        return return_value;
      }

#ifdef MSG_TO_STRING 
      ::EmbeddedProto::string_view to_string_content(::EmbeddedProto::string_view& str, const uint32_t indent_level, const bool first_field) const
      {
        ::EmbeddedProto::string_view left_chars = str;

        switch(which_content_)
        {
          case FieldNumber::EMPTY:
            left_chars = content_.empty_.to_string(left_chars, indent_level, EMPTY_NAME, first_field);
            break;
          case FieldNumber::SEND_RF_REQUEST:
            left_chars = content_.send_rf_request_.to_string(left_chars, indent_level, SEND_RF_REQUEST_NAME, first_field);
            break;
          case FieldNumber::ERROR_MESSAGE:
            left_chars = content_.error_message_.to_string(left_chars, indent_level, ERROR_MESSAGE_NAME, first_field);
            break;
          case FieldNumber::RECEIVE_RF_REQUEST:
            left_chars = content_.receive_rf_request_.to_string(left_chars, indent_level, RECEIVE_RF_REQUEST_NAME, first_field);
            break;
          case FieldNumber::RECEIVE_RF_RESPONSE:
            left_chars = content_.receive_rf_response_.to_string(left_chars, indent_level, RECEIVE_RF_RESPONSE_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

} // End of namespace rfpelilo
#endif // RFPELILO_H