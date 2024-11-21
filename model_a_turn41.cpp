#include <iostream>
#include <google/protobuf/message.h>

// Define the protobuf message
protobuf::Message& CreateMessage() {
    protobuf::Example example;
    example.set_id(123);
    example.set_name("ProtoBuf Example");
    *example.mutable_nested() = CreateNestedMessage();
    return example;
}

protobuf::NestedMessage CreateNestedMessage() {
    protobuf::NestedMessage nested;
    nested.set_value(456);
    return nested;
}

int main() {
    // Create a protobuf message
    protobuf::Example example = CreateMessage();

    // Serialize the message to a string
    std::string serialized_data;
    if (!example.SerializeToString(&serialized_data)) {
        std::cerr << "Error serializing protobuf message." << std::endl;
        return 1;
    }
    std::cout << "Serialized data: " << serialized_data << std::endl;

    // Deserialize the message
    protobuf::Example example2;
    if (!example2.ParseFromString(serialized_data)) {
        std::cerr << "Error deserializing protobuf message." << std::endl;
        return 1;
    }
    std::cout << "Deserialized data: ID = " << example2.id()
              << ", Name = " << example2.name()
              << ", Nested Value = " << example2.nested().value() << std::endl;

    return 0;
}