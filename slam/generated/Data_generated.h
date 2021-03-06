// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DATA_THEMACHINEEU_H_
#define FLATBUFFERS_GENERATED_DATA_THEMACHINEEU_H_

#include "flatbuffers/flatbuffers.h"

#include "Register_generated.h"
#include "TrackedMotorThrottle_generated.h"

namespace themachineeu {

struct DataObject;

enum DataType {
  DataType_E_TrackedMotorThrottle = 0,
  DataType_E_Register = 1,
  DataType_MIN = DataType_E_TrackedMotorThrottle,
  DataType_MAX = DataType_E_Register
};

inline const DataType (&EnumValuesDataType())[2] {
  static const DataType values[] = {
    DataType_E_TrackedMotorThrottle,
    DataType_E_Register
  };
  return values;
}

inline const char * const *EnumNamesDataType() {
  static const char * const names[3] = {
    "E_TrackedMotorThrottle",
    "E_Register",
    nullptr
  };
  return names;
}

inline const char *EnumNameDataType(DataType e) {
  if (flatbuffers::IsOutRange(e, DataType_E_TrackedMotorThrottle, DataType_E_Register)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesDataType()[index];
}

enum Data {
  Data_NONE = 0,
  Data_TrackedMotorThrottle = 1,
  Data_Register = 2,
  Data_MIN = Data_NONE,
  Data_MAX = Data_Register
};

inline const Data (&EnumValuesData())[3] {
  static const Data values[] = {
    Data_NONE,
    Data_TrackedMotorThrottle,
    Data_Register
  };
  return values;
}

inline const char * const *EnumNamesData() {
  static const char * const names[4] = {
    "NONE",
    "TrackedMotorThrottle",
    "Register",
    nullptr
  };
  return names;
}

inline const char *EnumNameData(Data e) {
  if (flatbuffers::IsOutRange(e, Data_NONE, Data_Register)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesData()[index];
}

template<typename T> struct DataTraits {
  static const Data enum_value = Data_NONE;
};

template<> struct DataTraits<themachineeu::TrackedMotorThrottle> {
  static const Data enum_value = Data_TrackedMotorThrottle;
};

template<> struct DataTraits<themachineeu::Register> {
  static const Data enum_value = Data_Register;
};

bool VerifyData(flatbuffers::Verifier &verifier, const void *obj, Data type);
bool VerifyDataVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

struct DataObject FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_DTYPE = 4,
    VT_DATA_TYPE = 6,
    VT_DATA = 8
  };
  themachineeu::DataType dType() const {
    return static_cast<themachineeu::DataType>(GetField<int8_t>(VT_DTYPE, 0));
  }
  themachineeu::Data data_type() const {
    return static_cast<themachineeu::Data>(GetField<uint8_t>(VT_DATA_TYPE, 0));
  }
  const void *data() const {
    return GetPointer<const void *>(VT_DATA);
  }
  template<typename T> const T *data_as() const;
  const themachineeu::TrackedMotorThrottle *data_as_TrackedMotorThrottle() const {
    return data_type() == themachineeu::Data_TrackedMotorThrottle ? static_cast<const themachineeu::TrackedMotorThrottle *>(data()) : nullptr;
  }
  const themachineeu::Register *data_as_Register() const {
    return data_type() == themachineeu::Data_Register ? static_cast<const themachineeu::Register *>(data()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_DTYPE) &&
           VerifyField<uint8_t>(verifier, VT_DATA_TYPE) &&
           VerifyOffset(verifier, VT_DATA) &&
           VerifyData(verifier, data(), data_type()) &&
           verifier.EndTable();
  }
};

template<> inline const themachineeu::TrackedMotorThrottle *DataObject::data_as<themachineeu::TrackedMotorThrottle>() const {
  return data_as_TrackedMotorThrottle();
}

template<> inline const themachineeu::Register *DataObject::data_as<themachineeu::Register>() const {
  return data_as_Register();
}

struct DataObjectBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_dType(themachineeu::DataType dType) {
    fbb_.AddElement<int8_t>(DataObject::VT_DTYPE, static_cast<int8_t>(dType), 0);
  }
  void add_data_type(themachineeu::Data data_type) {
    fbb_.AddElement<uint8_t>(DataObject::VT_DATA_TYPE, static_cast<uint8_t>(data_type), 0);
  }
  void add_data(flatbuffers::Offset<void> data) {
    fbb_.AddOffset(DataObject::VT_DATA, data);
  }
  explicit DataObjectBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  DataObjectBuilder &operator=(const DataObjectBuilder &);
  flatbuffers::Offset<DataObject> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<DataObject>(end);
    return o;
  }
};

inline flatbuffers::Offset<DataObject> CreateDataObject(
    flatbuffers::FlatBufferBuilder &_fbb,
    themachineeu::DataType dType = themachineeu::DataType_E_TrackedMotorThrottle,
    themachineeu::Data data_type = themachineeu::Data_NONE,
    flatbuffers::Offset<void> data = 0) {
  DataObjectBuilder builder_(_fbb);
  builder_.add_data(data);
  builder_.add_data_type(data_type);
  builder_.add_dType(dType);
  return builder_.Finish();
}

inline bool VerifyData(flatbuffers::Verifier &verifier, const void *obj, Data type) {
  switch (type) {
    case Data_NONE: {
      return true;
    }
    case Data_TrackedMotorThrottle: {
      auto ptr = reinterpret_cast<const themachineeu::TrackedMotorThrottle *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Data_Register: {
      auto ptr = reinterpret_cast<const themachineeu::Register *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyDataVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyData(
        verifier,  values->Get(i), types->GetEnum<Data>(i))) {
      return false;
    }
  }
  return true;
}

inline const themachineeu::DataObject *GetDataObject(const void *buf) {
  return flatbuffers::GetRoot<themachineeu::DataObject>(buf);
}

inline const themachineeu::DataObject *GetSizePrefixedDataObject(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<themachineeu::DataObject>(buf);
}

inline const char *DataObjectIdentifier() {
  return "DATA";
}

inline bool DataObjectBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, DataObjectIdentifier());
}

inline bool VerifyDataObjectBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<themachineeu::DataObject>(DataObjectIdentifier());
}

inline bool VerifySizePrefixedDataObjectBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<themachineeu::DataObject>(DataObjectIdentifier());
}

inline void FinishDataObjectBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<themachineeu::DataObject> root) {
  fbb.Finish(root, DataObjectIdentifier());
}

inline void FinishSizePrefixedDataObjectBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<themachineeu::DataObject> root) {
  fbb.FinishSizePrefixed(root, DataObjectIdentifier());
}

}  // namespace themachineeu

#endif  // FLATBUFFERS_GENERATED_DATA_THEMACHINEEU_H_
