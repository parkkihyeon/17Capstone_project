FROM ubuntu:xenial

MAINTAINER seungsoo <nonestrike@gmail.com>
LABEL description="2017 Kookmin capstone reinforcement korean chess"

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y curl wget redis-server
RUN curl -sL https://deb.nodesource.com/setup_7.x | bash -
RUN apt-get install -y nodejs
RUN apt-get update
RUN apt-get install -y apt-utils
RUN apt-get install -y build-essential
RUN wget -O boost_1_63_0.tar.gz http://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.gz/download
RUN tar xzvf boost_1_63_0.tar.gz
RUN cd boost_1_63_0/ && ./bootstrap.sh --prefix=/usr/local/lib
RUN cd boost_1_63_0/ && ./b2
RUN cd boost_1_63_0/ && ./b2 install
RUN ulimit -s 512000
RUN npm install socket.io -g
RUN npm install socket.io-redis -g
RUN npm install net -g

WORKDIR /root/reinforcement

ADD ./src /root/reinforcement
RUN export LD_LIBRARY_PATH=/root/reinforcement:/usr/local/lib
RUN make

