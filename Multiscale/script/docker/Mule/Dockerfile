#####################################################################
#
# This Dockerfile is used to create the image containing Mule and all 
# dependent applications/libraries
#
#####################################################################

# Set the base image
FROM ubuntu

# Set the maintainer of the created image
MAINTAINER Ovidiu Parvu <ovidiu.parvu@gmail.com>

# Set environment variables accordingly
ENV BOOST_FOLDER_NAME Boost1.55
ENV MULE_FOLDER_NAME Mule
ENV OPENCV_FOLDER_NAME OpenCV2.4.10
ENV XERCES_FOLDER_NAME Xerces3.1.2

# Install required packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++-4.8 \
    gcc-4.8 \
    libc6-dev \
    libgtk2.0-dev \
    libicu-dev \
    libstdc++-4.8-dev \
    pkg-config \
    python2.7-dev \
    python-jinja2 \ 
    python-lxml \
    python-numpy \
    python-setuptools \
    unzip \
    wget

# Create a new directory for storing software
RUN mkdir -p home/user/software

# Change the working directory accordingly
WORKDIR /home/user/software

# Install Boost 1.55 
RUN mkdir $BOOST_FOLDER_NAME && cd $BOOST_FOLDER_NAME && wget http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.zip && unzip boost_1_55_0.zip && cd boost_1_55_0 && ./bootstrap.sh --prefix=/usr/local --with-libraries=filesystem,program_options,system && ./b2 install && /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/boost.conf' && ldconfig && cd ../../ && rm -rf $BOOST_FOLDER_NAME

# Install OpenCV 2.4.8
RUN mkdir $OPENCV_FOLDER_NAME && cd $OPENCV_FOLDER_NAME && wget http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.4.10/opencv-2.4.10.zip && unzip opencv-2.4.10.zip && cd opencv-2.4.10 && mkdir build && cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=OFF -D BUILD_NEW_PYTHON_SUPPORT=OFF -D WITH_V4L=OFF -D WITH_QT=OFF -D WITH_OPENGL=OFF .. && /bin/bash -c 'echo "make -j`nproc`"' && make install && /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf' && ldconfig && cd ../../../ && rm -rf $OPENCV_FOLDER_NAME

# Install Xerces 3.1.1
RUN mkdir $XERCES_FOLDER_NAME && cd $XERCES_FOLDER_NAME && wget http://mirror.catn.com/pub/apache//xerces/c/3/sources/xerces-c-3.1.2.tar.gz && tar -xvzf xerces-c-3.1.2.tar.gz && cd xerces-c-3.1.2 && ./configure --prefix=/usr/local --libdir=/usr/local/lib && /bin/bash -c 'echo "make -j`nproc`"' && make install && /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/xerces.conf' && ldconfig && cd ../../ && rm -rf $XERCES_FOLDER_NAME

# Download and install Mule
RUN mkdir $MULE_FOLDER_NAME && cd $MULE_FOLDER_NAME && wget https://github.com/IceRage/Mule/archive/master.zip && unzip master.zip && cd Mule-master/Multiscale && rm -rf build && mkdir -p build/Release && cd build/Release && cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -DCMAKE_CUSTOM_BUILD_TYPE=Package -DCMAKE_CUSTOM_MODEL_CHECKER=Generate ../../ && /bin/bash -c 'echo "make -j`nproc`"' && make install && cd ../../../../ && mv Mule-master/* . && rm -rf Mule-master/ master.zip 
