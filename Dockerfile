FROM ubuntu:latest AS build
RUN apt-get update && apt-get install -y g++ cmake make git cppcheck clang-tidy
WORKDIR /app
COPY . .
RUN make calc_cli 

FROM ubuntu:latest AS run
COPY --from=build /app/build/calc_cli /usr/bin/
COPY --from=build /app/build/lib* /usr/lib/
RUN ln -s /usr/bin/calc_cli /usr/bin/calc

ENTRYPOINT ["/bin/bash"]
