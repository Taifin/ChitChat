// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#include "message.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace ChitChatMessage {
constexpr Query_User::Query_User(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , password_(nullptr)
  , skin_(nullptr)
  , x_coord_(0)
  , y_coord_(0){}
struct Query_UserDefaultTypeInternal {
  constexpr Query_UserDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~Query_UserDefaultTypeInternal() {}
  union {
    Query_User _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT Query_UserDefaultTypeInternal _Query_User_default_instance_;
constexpr Query::Query(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : user_(nullptr)
  , rtype_(0)
{}
struct QueryDefaultTypeInternal {
  constexpr QueryDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~QueryDefaultTypeInternal() {}
  union {
    Query _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT QueryDefaultTypeInternal _Query_default_instance_;
}  // namespace ChitChatMessage
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_message_2eproto[2];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_message_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_message_2eproto = nullptr;

const uint32_t TableStruct_message_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query_User, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query_User, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query_User, name_),
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query_User, password_),
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query_User, skin_),
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query_User, x_coord_),
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query_User, y_coord_),
  0,
  1,
  2,
  3,
  4,
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query, rtype_),
  PROTOBUF_FIELD_OFFSET(::ChitChatMessage::Query, user_),
  1,
  0,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 11, -1, sizeof(::ChitChatMessage::Query_User)},
  { 16, 24, -1, sizeof(::ChitChatMessage::Query)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ChitChatMessage::_Query_User_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ChitChatMessage::_Query_default_instance_),
};

const char descriptor_table_protodef_message_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rmessage.proto\022\017ChitChatMessage\"\334\002\n\005Que"
  "ry\0221\n\005rType\030\001 \002(\0162\".ChitChatMessage.Quer"
  "y.RequestType\022)\n\004user\030\002 \002(\0132\033.ChitChatMe"
  "ssage.Query.User\032i\n\004User\022\014\n\004name\030\001 \002(\t\022\025"
  "\n\010password\030\002 \001(\t:\003pwd\022\024\n\004skin\030\003 \001(\t:\006ker"
  "mit\022\022\n\007x_coord\030\004 \001(\005:\0010\022\022\n\007y_coord\030\005 \001(\005"
  ":\0010\"\211\001\n\013RequestType\022\t\n\005LOGIN\020\000\022\014\n\010REGIST"
  "ER\020\001\022\013\n\007CONNECT\020\003\022\010\n\004MOVE\020\004\022\016\n\nDISCONNEC"
  "T\020\005\022\017\n\013CHANGE_SKIN\020\006\022\020\n\014CHANGE_SCORE\020\007\022\014"
  "\n\010GET_SKIN\020\010\022\t\n\005HELLO\020\t"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_message_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_message_2eproto = {
  false, false, 383, descriptor_table_protodef_message_2eproto, "message.proto", 
  &descriptor_table_message_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_message_2eproto::offsets,
  file_level_metadata_message_2eproto, file_level_enum_descriptors_message_2eproto, file_level_service_descriptors_message_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_message_2eproto_getter() {
  return &descriptor_table_message_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_message_2eproto(&descriptor_table_message_2eproto);
namespace ChitChatMessage {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Query_RequestType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_message_2eproto);
  return file_level_enum_descriptors_message_2eproto[0];
}
bool Query_RequestType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      return true;
    default:
      return false;
  }
}

#if (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))
constexpr Query_RequestType Query::LOGIN;
constexpr Query_RequestType Query::REGISTER;
constexpr Query_RequestType Query::CONNECT;
constexpr Query_RequestType Query::MOVE;
constexpr Query_RequestType Query::DISCONNECT;
constexpr Query_RequestType Query::CHANGE_SKIN;
constexpr Query_RequestType Query::CHANGE_SCORE;
constexpr Query_RequestType Query::GET_SKIN;
constexpr Query_RequestType Query::HELLO;
constexpr Query_RequestType Query::RequestType_MIN;
constexpr Query_RequestType Query::RequestType_MAX;
constexpr int Query::RequestType_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || (_MSC_VER >= 1900 && _MSC_VER < 1912))

// ===================================================================

class Query_User::_Internal {
 public:
  using HasBits = decltype(std::declval<Query_User>()._has_bits_);
  static void set_has_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_password(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_skin(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_x_coord(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_y_coord(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000001) ^ 0x00000001) != 0;
  }
};

const ::PROTOBUF_NAMESPACE_ID::internal::LazyString Query_User::_i_give_permission_to_break_this_code_default_password_{{{"pwd", 3}}, {nullptr}};
const ::PROTOBUF_NAMESPACE_ID::internal::LazyString Query_User::_i_give_permission_to_break_this_code_default_skin_{{{"kermit", 6}}, {nullptr}};
Query_User::Query_User(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:ChitChatMessage.Query.User)
}
Query_User::Query_User(const Query_User& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_name()) {
    name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(), 
      GetArenaForAllocation());
  }
  password_.UnsafeSetDefault(nullptr);
  if (from._internal_has_password()) {
    password_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::NonEmptyDefault{}, from._internal_password(), 
      GetArenaForAllocation());
  }
  skin_.UnsafeSetDefault(nullptr);
  if (from._internal_has_skin()) {
    skin_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::NonEmptyDefault{}, from._internal_skin(), 
      GetArenaForAllocation());
  }
  ::memcpy(&x_coord_, &from.x_coord_,
    static_cast<size_t>(reinterpret_cast<char*>(&y_coord_) -
    reinterpret_cast<char*>(&x_coord_)) + sizeof(y_coord_));
  // @@protoc_insertion_point(copy_constructor:ChitChatMessage.Query.User)
}

inline void Query_User::SharedCtor() {
name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
password_.UnsafeSetDefault(nullptr);
skin_.UnsafeSetDefault(nullptr);
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&x_coord_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&y_coord_) -
    reinterpret_cast<char*>(&x_coord_)) + sizeof(y_coord_));
}

Query_User::~Query_User() {
  // @@protoc_insertion_point(destructor:ChitChatMessage.Query.User)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Query_User::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  password_.DestroyNoArena(nullptr);
  skin_.DestroyNoArena(nullptr);
}

void Query_User::ArenaDtor(void* object) {
  Query_User* _this = reinterpret_cast< Query_User* >(object);
  (void)_this;
}
void Query_User::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Query_User::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Query_User::Clear() {
// @@protoc_insertion_point(message_clear_start:ChitChatMessage.Query.User)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      name_.ClearNonDefaultToEmpty();
    }
    if (cached_has_bits & 0x00000002u) {
      password_.ClearToDefault(::ChitChatMessage::Query_User::_i_give_permission_to_break_this_code_default_password_, GetArenaForAllocation());
       }
    if (cached_has_bits & 0x00000004u) {
      skin_.ClearToDefault(::ChitChatMessage::Query_User::_i_give_permission_to_break_this_code_default_skin_, GetArenaForAllocation());
       }
  }
  if (cached_has_bits & 0x00000018u) {
    ::memset(&x_coord_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&y_coord_) -
        reinterpret_cast<char*>(&x_coord_)) + sizeof(y_coord_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Query_User::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // required string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "ChitChatMessage.Query.User.name");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional string password = 2 [default = "pwd"];
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_password();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "ChitChatMessage.Query.User.password");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional string skin = 3 [default = "kermit"];
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_skin();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "ChitChatMessage.Query.User.skin");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional int32 x_coord = 4 [default = 0];
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _Internal::set_has_x_coord(&has_bits);
          x_coord_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional int32 y_coord = 5 [default = 0];
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _Internal::set_has_y_coord(&has_bits);
          y_coord_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Query_User::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ChitChatMessage.Query.User)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string name = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "ChitChatMessage.Query.User.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  // optional string password = 2 [default = "pwd"];
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_password().data(), static_cast<int>(this->_internal_password().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "ChitChatMessage.Query.User.password");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_password(), target);
  }

  // optional string skin = 3 [default = "kermit"];
  if (cached_has_bits & 0x00000004u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_skin().data(), static_cast<int>(this->_internal_skin().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "ChitChatMessage.Query.User.skin");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_skin(), target);
  }

  // optional int32 x_coord = 4 [default = 0];
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(4, this->_internal_x_coord(), target);
  }

  // optional int32 y_coord = 5 [default = 0];
  if (cached_has_bits & 0x00000010u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(5, this->_internal_y_coord(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ChitChatMessage.Query.User)
  return target;
}

size_t Query_User::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ChitChatMessage.Query.User)
  size_t total_size = 0;

  // required string name = 1;
  if (_internal_has_name()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000001eu) {
    // optional string password = 2 [default = "pwd"];
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_password());
    }

    // optional string skin = 3 [default = "kermit"];
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_skin());
    }

    // optional int32 x_coord = 4 [default = 0];
    if (cached_has_bits & 0x00000008u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_x_coord());
    }

    // optional int32 y_coord = 5 [default = 0];
    if (cached_has_bits & 0x00000010u) {
      total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_y_coord());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Query_User::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Query_User::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Query_User::GetClassData() const { return &_class_data_; }

void Query_User::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Query_User *>(to)->MergeFrom(
      static_cast<const Query_User &>(from));
}


void Query_User::MergeFrom(const Query_User& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ChitChatMessage.Query.User)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_name(from._internal_name());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_set_password(from._internal_password());
    }
    if (cached_has_bits & 0x00000004u) {
      _internal_set_skin(from._internal_skin());
    }
    if (cached_has_bits & 0x00000008u) {
      x_coord_ = from.x_coord_;
    }
    if (cached_has_bits & 0x00000010u) {
      y_coord_ = from.y_coord_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Query_User::CopyFrom(const Query_User& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ChitChatMessage.Query.User)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Query_User::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_has_bits_)) return false;
  return true;
}

void Query_User::InternalSwap(Query_User* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &name_, lhs_arena,
      &other->name_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      nullptr,
      &password_, lhs_arena,
      &other->password_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      nullptr,
      &skin_, lhs_arena,
      &other->skin_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Query_User, y_coord_)
      + sizeof(Query_User::y_coord_)
      - PROTOBUF_FIELD_OFFSET(Query_User, x_coord_)>(
          reinterpret_cast<char*>(&x_coord_),
          reinterpret_cast<char*>(&other->x_coord_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Query_User::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_message_2eproto_getter, &descriptor_table_message_2eproto_once,
      file_level_metadata_message_2eproto[0]);
}

// ===================================================================

class Query::_Internal {
 public:
  using HasBits = decltype(std::declval<Query>()._has_bits_);
  static void set_has_rtype(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static const ::ChitChatMessage::Query_User& user(const Query* msg);
  static void set_has_user(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static bool MissingRequiredFields(const HasBits& has_bits) {
    return ((has_bits[0] & 0x00000003) ^ 0x00000003) != 0;
  }
};

const ::ChitChatMessage::Query_User&
Query::_Internal::user(const Query* msg) {
  return *msg->user_;
}
Query::Query(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:ChitChatMessage.Query)
}
Query::Query(const Query& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_user()) {
    user_ = new ::ChitChatMessage::Query_User(*from.user_);
  } else {
    user_ = nullptr;
  }
  rtype_ = from.rtype_;
  // @@protoc_insertion_point(copy_constructor:ChitChatMessage.Query)
}

inline void Query::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&user_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&rtype_) -
    reinterpret_cast<char*>(&user_)) + sizeof(rtype_));
}

Query::~Query() {
  // @@protoc_insertion_point(destructor:ChitChatMessage.Query)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Query::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete user_;
}

void Query::ArenaDtor(void* object) {
  Query* _this = reinterpret_cast< Query* >(object);
  (void)_this;
}
void Query::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Query::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Query::Clear() {
// @@protoc_insertion_point(message_clear_start:ChitChatMessage.Query)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(user_ != nullptr);
    user_->Clear();
  }
  rtype_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Query::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // required .ChitChatMessage.Query.RequestType rType = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::ChitChatMessage::Query_RequestType_IsValid(val))) {
            _internal_set_rtype(static_cast<::ChitChatMessage::Query_RequestType>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else
          goto handle_unusual;
        continue;
      // required .ChitChatMessage.Query.User user = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_user(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Query::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ChitChatMessage.Query)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .ChitChatMessage.Query.RequestType rType = 1;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_rtype(), target);
  }

  // required .ChitChatMessage.Query.User user = 2;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::user(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ChitChatMessage.Query)
  return target;
}

size_t Query::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:ChitChatMessage.Query)
  size_t total_size = 0;

  if (_internal_has_user()) {
    // required .ChitChatMessage.Query.User user = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *user_);
  }

  if (_internal_has_rtype()) {
    // required .ChitChatMessage.Query.RequestType rType = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_rtype());
  }

  return total_size;
}
size_t Query::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ChitChatMessage.Query)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required .ChitChatMessage.Query.User user = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *user_);

    // required .ChitChatMessage.Query.RequestType rType = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_rtype());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Query::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Query::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Query::GetClassData() const { return &_class_data_; }

void Query::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Query *>(to)->MergeFrom(
      static_cast<const Query &>(from));
}


void Query::MergeFrom(const Query& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ChitChatMessage.Query)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_user()->::ChitChatMessage::Query_User::MergeFrom(from._internal_user());
    }
    if (cached_has_bits & 0x00000002u) {
      rtype_ = from.rtype_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Query::CopyFrom(const Query& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ChitChatMessage.Query)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Query::IsInitialized() const {
  if (_Internal::MissingRequiredFields(_has_bits_)) return false;
  if (_internal_has_user()) {
    if (!user_->IsInitialized()) return false;
  }
  return true;
}

void Query::InternalSwap(Query* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Query, rtype_)
      + sizeof(Query::rtype_)
      - PROTOBUF_FIELD_OFFSET(Query, user_)>(
          reinterpret_cast<char*>(&user_),
          reinterpret_cast<char*>(&other->user_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Query::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_message_2eproto_getter, &descriptor_table_message_2eproto_once,
      file_level_metadata_message_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace ChitChatMessage
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ChitChatMessage::Query_User* Arena::CreateMaybeMessage< ::ChitChatMessage::Query_User >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ChitChatMessage::Query_User >(arena);
}
template<> PROTOBUF_NOINLINE ::ChitChatMessage::Query* Arena::CreateMaybeMessage< ::ChitChatMessage::Query >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ChitChatMessage::Query >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>