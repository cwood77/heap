all: debug

debug: bin/out/debug/heapbin.dll bin/out/debug/heaplib.lib bin/out/debug/demo.exe bin/out/debug/instrument.exe

.PHONY: all debug

bin/out/debug/heapbin.dll : bin/int/1/heapbin.dll
	@cp $< $@

bin/out/debug/heaplib.lib : bin/int/2/heaplib.lib
	@cp $< $@

bin/out/debug/demo.exe : bin/int/3/demo.exe
	@cp $< $@

bin/out/debug/instrument.exe : bin/int/3/instrument.exe
	@cp $< $@

bin/int/0/heapbin-heap.o : src/heapbin/heap.cpp src/heapbin/api.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/heapbin/heap.cpp -o $@

bin/int/0/heapbin-intf.o : src/heapbin/intf.cpp src/heapbin/api.hpp src/heapbin/heap-i.hpp src/heapbin/probes-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/heapbin/intf.cpp -o $@

bin/int/0/heapbin-probes.o : src/heapbin/probes.cpp src/heapbin/api.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/heapbin/probes.cpp -o $@

bin/int/0/heaplib-api.o : src/heaplib/api.cpp src/heapbin/api.hpp src/heaplib/api.h src/heaplib/probe.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/heaplib/api.cpp -o $@

bin/int/0/demo-main.o : src/demo/main.cpp src/heaplib/hooks.h src/heaplib/probe.hpp src/demo/cmd-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/demo/main.cpp -o $@

bin/int/0/demo-type.scalarnew.o : src/demo/type.scalarnew.cpp src/heaplib/hooks.h src/heaplib/probe.hpp src/demo/cmd-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/demo/type.scalarnew.cpp -o $@

bin/int/0/instrument-finder.o : src/instrument/finder.cpp src/instrument/api-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/instrument/finder.cpp -o $@

bin/int/0/instrument-instrumetor.o : src/instrument/instrumetor.cpp src/instrument/api-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/instrument/instrumetor.cpp -o $@

bin/int/0/instrument-main.o : src/instrument/main.cpp src/instrument/api-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/instrument/main.cpp -o $@

bin/int/0/instrument-template.hook.o : src/instrument/template.hook.cpp src/instrument/api-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/instrument/template.hook.cpp -o $@

bin/int/0/instrument-template.main.o : src/instrument/template.main.cpp src/instrument/api-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/instrument/template.main.cpp -o $@

bin/int/0/instrument-template.probe.o : src/instrument/template.probe.cpp src/instrument/api-i.hpp
	$(info $< --> $@)
	@x86_64-w64-mingw32-g++ -ggdb -D cdwDebugMode -c -Wall -D cdwTest -Wno-invalid-offsetof -D cdwAppDataName=\"gaudi\" src/instrument/template.probe.cpp -o $@

bin/int/1/heapbin.dll : bin/int/0/heapbin-heap.o bin/int/0/heapbin-intf.o bin/int/0/heapbin-probes.o
	$(info   * --> $@)
	@x86_64-w64-mingw32-g++ -shared -o $@  bin/int/0/heapbin-heap.o bin/int/0/heapbin-intf.o bin/int/0/heapbin-probes.o -ggdb -static-libgcc -static-libstdc++ -static

bin/int/2/heaplib.lib : bin/int/0/heaplib-api.o
	$(info   * --> $@)
	@ar crs $@  bin/int/0/heaplib-api.o

bin/int/3/demo.exe : bin/int/0/demo-main.o bin/int/0/demo-type.scalarnew.o bin/int/2/heaplib.lib
	$(info   * --> $@)
	@x86_64-w64-mingw32-g++ -o $@  bin/int/0/demo-main.o bin/int/0/demo-type.scalarnew.o -ggdb -static-libgcc -static-libstdc++ -static -Lbin/int/2 -lheaplib

bin/int/3/instrument.exe : bin/int/0/instrument-finder.o bin/int/0/instrument-instrumetor.o bin/int/0/instrument-main.o bin/int/0/instrument-template.hook.o bin/int/0/instrument-template.main.o bin/int/0/instrument-template.probe.o
	$(info   * --> $@)
	@x86_64-w64-mingw32-g++ -o $@  bin/int/0/instrument-finder.o bin/int/0/instrument-instrumetor.o bin/int/0/instrument-main.o bin/int/0/instrument-template.hook.o bin/int/0/instrument-template.main.o bin/int/0/instrument-template.probe.o -ggdb -static-libgcc -static-libstdc++ -static

