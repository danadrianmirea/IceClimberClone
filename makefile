CXX=g++
SDKROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk
CFLAGS=-std=c++11 -stdlib=libc++ -Ofast -Wno-deprecated -I/usr/local/Cellar/glfw/3.3/include/ -I/usr/local/include -I. -Isrc/ -Ithird_party -isysroot $(SDKROOT)
LDFLAGS=-Wl,-search_paths_first -Wl,-headerpad_max_install_names -framework OpenGL -framework Cocoa -lGLFW -L/usr/local/Cellar/glfw/3.3/lib/
EXEC=main
SIZE=size -B -d

all: glad.o float_double_buffer.o uint16_double_buffer.o position.o vec2.o scene_object.o scene_object_factory.o main_character.o brick.o brick_brown.o brick_blue.o brick_green_half.o brick_brown_half.o brick_blue_half.o state_machine.o scene_object_manager.o sprite.o sprite_texture.o object_sprite_sheet_animation.o object_sprite_sheet.o scene_object_texture_manager.o
	$(CXX) $(CFLAGS) $(LDFLAGS) main.cpp scene_object.o scene_object_factory.o main_character.o brick.o brick_brown.o brick_blue.o brick_green_half.o brick_brown_half.o brick_blue_half.o state_machine.o scene_object_manager.o sprite.o sprite_texture.o scene_object_texture_manager.o object_sprite_sheet.o object_sprite_sheet_animation.o position.o vec2.o float_double_buffer.o uint16_double_buffer.o glad.o -o $(EXEC)
	$(SIZE) $(EXEC)

main_character.o: src/items/main_character.cpp
	$(CXX) -c $(CFLAGS) src/items/main_character.cpp

brick.o: src/items/brick.cpp
	$(CXX) -c $(CFLAGS) src/items/brick.cpp

brick_brown.o: src/items/brick_brown.cpp
	$(CXX) -c $(CFLAGS) src/items/brick_brown.cpp

brick_blue.o: src/items/brick_blue.cpp
	$(CXX) -c $(CFLAGS) src/items/brick_blue.cpp

brick_green_half.o: src/items/brick_green_half.cpp
	$(CXX) -c $(CFLAGS) src/items/brick_green_half.cpp

brick_brown_half.o: src/items/brick_brown_half.cpp
	$(CXX) -c $(CFLAGS) src/items/brick_brown_half.cpp

brick_blue_half.o: src/items/brick_blue_half.cpp
	$(CXX) -c $(CFLAGS) src/items/brick_blue_half.cpp

state_machine.o: src/state_machine.cpp
	$(CXX) -c $(CFLAGS) src/state_machine.cpp

scene_object_factory.o: src/scene_object_factory.cpp
	$(CXX) -c $(CFLAGS) src/scene_object_factory.cpp

scene_object_texture_manager.o: src/scene_object_texture_manager.cpp
	$(CXX) -c $(CFLAGS) src/scene_object_texture_manager.cpp

scene_object_manager.o: src/scene_object_manager.cpp
	$(CXX) -c $(CFLAGS) src/scene_object_manager.cpp

scene_object.o: src/scene_object.cpp
	$(CXX) -c $(CFLAGS) src/scene_object.cpp

object_sprite_sheet.o: src/object_sprite_sheet.cpp
	$(CXX) -c $(CFLAGS) src/object_sprite_sheet.cpp

object_sprite_sheet_animation.o: src/object_sprite_sheet_animation.cpp
	$(CXX) -c $(CFLAGS) src/object_sprite_sheet_animation.cpp

sprite_texture.o: src/sprite_texture.cpp
	$(CXX) -c $(CFLAGS) src/sprite_texture.cpp

sprite.o: src/sprite.cpp
	$(CXX) -c $(CFLAGS) src/sprite.cpp

vec2.o: src/vec2.cpp
	$(CXX) -c $(CFLAGS) src/vec2.cpp

position.o: src/position.cpp
	$(CXX) -c $(CFLAGS) src/position.cpp

uint16_double_buffer.o: src/uint16_double_buffer.cpp
	$(CXX) -c $(CFLAGS) src/uint16_double_buffer.cpp

float_double_buffer.o: src/float_double_buffer.cpp
	$(CXX) -c $(CFLAGS) src/float_double_buffer.cpp

glad.o: third_party/glad/glad.cpp
	$(CXX) -c $(CFLAGS) third_party/glad/glad.cpp

clean:
	rm -f $(EXEC) *.o *.gch src/*.o src/*.gch
