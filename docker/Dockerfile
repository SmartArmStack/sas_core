FROM murilomarinho/sas:jazzy
LABEL authors="murilomarinho"
SHELL ["/bin/bash", "-c"]
ENV BASH_ENV="/etc/bash_env"

RUN sudo apt-get update && sudo apt-get upgrade -y

# Remove the legacy monolithic sas_core package shipped by the base image;
# it would otherwise shadow this thin wrapper.
RUN sudo apt-get remove -y ros-jazzy-sas-core

# Python bindings from PyPI (self-contained wheel, core statically linked).
# dqrobotics (python) is already present in the base image.
RUN python3 -m pip install --upgrade marinholab-sas-core --break-system-packages

# C++ core .deb -- TEMPORARY: built from source because the
# libmarinholab-sas-core .deb is not yet published to an apt repository.
# libdqrobotics (C++) is already present in the base image, so no PPA is
# needed here. The build is architecture-agnostic (amd64 or arm64).
#
# Once the .deb is published to an apt repository, replace this block with:
#   RUN sudo apt-get update \
#       && sudo apt-get install -y libmarinholab-sas-core
RUN sudo apt-get update \
    && sudo apt-get install -y debhelper dpkg-dev \
    && git clone --depth 1 --branch 26.09 https://github.com/MarinhoLab/sas_cpp.git /tmp/sas_cpp \
    && cd /tmp/sas_cpp \
    && dpkg-buildpackage -us -uc -b \
    && cd /tmp \
    && sudo dpkg -i ./libmarinholab-sas-core_*.deb \
    && sudo rm -rf /tmp/sas_cpp /tmp/libmarinholab-sas-core_*.deb

RUN mkdir -p /root/sas_core_devel/src/
COPY . /root/sas_core_devel/src/sas_core
