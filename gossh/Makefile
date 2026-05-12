BINARY := gossh
LDFLAGS := -s -w

.PHONY: all clean darwin linux windows

all: darwin linux windows

darwin:
	GOOS=darwin GOARCH=amd64 go build -ldflags="$(LDFLAGS)" -o $(BINARY)-darwin .

linux:
	GOOS=linux GOARCH=amd64 go build -ldflags="$(LDFLAGS)" -o $(BINARY)-linux .

windows:
	GOOS=windows GOARCH=amd64 go build -ldflags="$(LDFLAGS)" -o $(BINARY)-windows.exe .

clean:
	rm -f $(BINARY)-darwin $(BINARY)-linux $(BINARY)-windows.exe
