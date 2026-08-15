FROM murilomarinho/sas:jazzy
LABEL authors="murilomarinho"
SHELL ["/bin/bash", "-c"]
ENV BASH_ENV="/etc/bash_env"

RUN sudo apt-get update && sudo apt-get upgrade -y
RUN python3 -m pip install --upgrade dqrobotics --break-system-packages
RUN sudo sudo apt-get remove -y ros-jazzy-sas-core
RUN mkdir -p /root/sas_core_devel/src/
COPY . /root/sas_core_devel/src/sas_core
COPY test_consumer /root/sas_core_devel/src/test_consumer