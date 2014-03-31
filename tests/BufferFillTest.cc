
#include <xcdf/XCDF.h>

#include <cstdio>

int main(int argc, char** argv) {

  XCDFFile f("buffertest.xcd", "w");
  XCDFUnsignedIntegerField field1 =
                  f.AllocateUnsignedIntegerField("field1", 1);
  XCDFUnsignedIntegerField field2 =
                  f.AllocateUnsignedIntegerField("field2", 4);
  XCDFSignedIntegerField field3 =
                  f.AllocateSignedIntegerField("field3", 2);
  XCDFFloatingPointField field4 =
                  f.AllocateFloatingPointField("field4", 0.);
  XCDFFloatingPointField field5 =
                  f.AllocateFloatingPointField("field5", 0., "field1");
  XCDFUnsignedIntegerField field6 =
                  f.AllocateUnsignedIntegerField("field6", 1);

  f.SetBlockSize(100000000);
  f.SetBlockThresholdByteCount(400000000);

  for (int k = 0; k < 8000001; k++) {
    field1 << 7;
    field2 << k;
    field3 << -1;
    field4 << 101.3;
    field5 << 0.2 << 3.9 << 222.3 << 10840.4 << 3.9 << 222.3 << 10840.4;
    field6 << k;
    f.Write();
  }

  f.SetBlockSize(1000);

  for (int k = 0; k < 5000000; k++) {
    field1 << 7;
    field2 << k;
    field3 << -1;
    field4 << 101.3;
    field5 << 0.2 << 3.9 << 222.3 << 10840.4 << 3.9 << 222.3 << 10840.4;
    field6 << k;
    f.Write();
  }

  f.AddComment("buffer fill test file");

  std::cout << "Writing test file: " << f.GetEventCount()
                                    << " entries." << std::endl;

  f.Close();

  XCDFFile h("buffertest.xcd", "r");

  // Count the entries
  unsigned count = h.GetEventCount();

  std::cout << "Reading file: " << count << " entries." << std::endl;

  h.Rewind();

  h.Read();

  field1 = h.GetUnsignedIntegerField("field1");
  field2 = h.GetUnsignedIntegerField("field2");
  field3 = h.GetSignedIntegerField("field3");
  field4 = h.GetFloatingPointField("field4");
  field5 = h.GetFloatingPointField("field5");
  field6 = h.GetUnsignedIntegerField("field6");

  std::cout << "Field 1: " << *field1 << std::endl;
  std::cout << "Field 2: " << *field2 << std::endl;
  std::cout << "Field 3: " << *field3 << std::endl;
  std::cout << "Field 4: " << *field4 << std::endl;
  std::cout << "Field 5: ";
  for (unsigned k = 0; k < *field1; k++ ) {
    std::cout << field5[k] << " ";
  }
  std::cout << std::endl;
  std::cout << "Field 6: " << *field6 << std::endl;

  std::cout << std::endl << "Reading events!" << std::endl;

  for (int k = 0; k < 13000000; k++ ) {
    h.Read();
  }

  std::cout << "Field 1: " << *field1 << std::endl;
  std::cout << "Field 2: " << *field2 << std::endl;
  std::cout << "Field 3: " << *field3 << std::endl;
  std::cout << "Field 4: " << *field4 << std::endl;
  std::cout << "Field 5: ";
  for (unsigned k = 0; k < *field1; k++ ) {
    std::cout << field5[k] << " ";
  }
  std::cout << std::endl;
  std::cout << "Field 6: " << *field6 << std::endl;

  h.Close();
}
