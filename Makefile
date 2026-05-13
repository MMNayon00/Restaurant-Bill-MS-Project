CC=gcc
CFLAGS=-Wall -Wextra -std=c99
TARGET=restaurant_bill
SOURCE=Restaurant\ Bill.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

check: $(TARGET)
	@echo "Build successful. Checking if binary exists..."
	@if [ -f $(TARGET) ]; then echo "Binary $(TARGET) exists."; else echo "Binary not found."; exit 1; fi

distcheck: $(TARGET)
	@echo "Distribution check: Build successful."
	@if [ -f $(TARGET) ]; then echo "Binary $(TARGET) ready for distribution."; else echo "Binary not found."; exit 1; fi

clean:
	rm -f $(TARGET) RestaurantBill.dat

.PHONY: all check distcheck clean