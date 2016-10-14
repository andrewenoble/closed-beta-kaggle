FROM ubuntu:16.04
RUN apt-get update && \
    apt-get install -y clang-3.5
COPY test.cpp /bin/test.cpp
WORKDIR /bin
RUN clang++-3.5 -std=c++11 -Ofast -march=native -flto /bin/test.cpp -o test.out
RUN chmod 755 /bin/test.out
ENTRYPOINT ["/bin/test.out"]
