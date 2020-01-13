// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_REGISTER_THEMACHINEEU_H_
#define FLATBUFFERS_GENERATED_REGISTER_THEMACHINEEU_H_

#include "flatbuffers/flatbuffers.h"

namespace themachineeu {

struct Register;

enum UserType {
  UserType_Slam = 0,
  UserType_Drive = 1,
  UserType_MIN = UserType_Slam,
  UserType_MAX = UserType_Drive
};

inline const UserType (&EnumValuesUserType())[2] {
  static const UserType values[] = {
    UserType_Slam,
    UserType_Drive
  };
  return values;
}

inline const char * const *EnumNamesUserType() {
  static const char * const names[3] = {
    "Slam",
    "Drive",
    nullptr
  };
  return names;
}

inline const char *EnumNameUserType(UserType e) {
  if (flatbuffers::IsOutRange(e, UserType_Slam, UserType_Drive)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesUserType()[index];
}

struct Register FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_USERTYPE = 6
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  themachineeu::UserType userType() const {
    return static_cast<themachineeu::UserType>(GetField<int8_t>(VT_USERTYPE, 0));
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<int8_t>(verifier, VT_USERTYPE) &&
           verifier.EndTable();
  }
};

struct RegisterBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Register::VT_NAME, name);
  }
  void add_userType(themachineeu::UserType userType) {
    fbb_.AddElement<int8_t>(Register::VT_USERTYPE, static_cast<int8_t>(userType), 0);
  }
  explicit RegisterBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RegisterBuilder &operator=(const RegisterBuilder &);
  flatbuffers::Offset<Register> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Register>(end);
    return o;
  }
};

inline flatbuffers::Offset<Register> CreateRegister(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    themachineeu::UserType userType = themachineeu::UserType_Slam) {
  RegisterBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_userType(userType);
  return builder_.Finish();
}

inline flatbuffers::Offset<Register> CreateRegisterDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    themachineeu::UserType userType = themachineeu::UserType_Slam) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return themachineeu::CreateRegister(
      _fbb,
      name__,
      userType);
}

inline const themachineeu::Register *GetRegister(const void *buf) {
  return flatbuffers::GetRoot<themachineeu::Register>(buf);
}

inline const themachineeu::Register *GetSizePrefixedRegister(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<themachineeu::Register>(buf);
}

inline const char *RegisterIdentifier() {
  return "REGI";
}

inline bool RegisterBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, RegisterIdentifier());
}

inline bool VerifyRegisterBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<themachineeu::Register>(RegisterIdentifier());
}

inline bool VerifySizePrefixedRegisterBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<themachineeu::Register>(RegisterIdentifier());
}

inline void FinishRegisterBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<themachineeu::Register> root) {
  fbb.Finish(root, RegisterIdentifier());
}

inline void FinishSizePrefixedRegisterBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<themachineeu::Register> root) {
  fbb.FinishSizePrefixed(root, RegisterIdentifier());
}

}  // namespace themachineeu

#endif  // FLATBUFFERS_GENERATED_REGISTER_THEMACHINEEU_H_
