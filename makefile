
# Makefile — build app + build hot-reloadable game.so from src/game.cpp
#
# Usage:
#   make            # build app + game.so
#   make app        # build only the executable
#   make game       # rebuild game.so (timestamped -> moved to game.so)
#   make run        # build then run ./app
#   make clean

CXX      := g++
CXXFLAGS := -std=c++20 -O2 -g

# Your warnings (normalized: add -W prefix, remove stray spaces)
WARNINGS := -Wno-writable-strings -Wno-format-security -Wno-deprecated-declarations -Wno-switch

# Includes / libs (edit these to match your project)
INCLUDES := -Isrc -Ithird_party -Ithird_party/Include
LIBS     := -lX11 -lGL -ldl -lpthread

# Layout
SRC_DIR  := src
OBJ_DIR  := build

APP      := app
GAME_SRC := $(SRC_DIR)/game.cpp
GAME_SO  := game.so

# Compile every .cpp in src EXCEPT game.cpp into the main executable.
APP_SRCS := $(filter-out $(GAME_SRC),$(wildcard $(SRC_DIR)/*.cpp))
APP_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(APP_SRCS))

# Default
.PHONY: all
all: $(APP) game

# Ensure obj dir exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Object build
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@

# Link app
$(APP): $(APP_OBJS)
	$(CXX) $(CXXFLAGS) $(APP_OBJS) -o $@ $(LIBS)

# Hot-reload library build:
# - timestamped build artifact -> atomically moved into game.so
.PHONY: game
game:
	@ts=$$(date +%s); \
	out=game_$$ts.so; \
	echo "[GAME] Building $$out -> $(GAME_SO)"; \
	rm -f game_*.so; \
	$(CXX) $(CXXFLAGS) -fPIC $(WARNINGS) $(INCLUDES) -shared $(GAME_SRC) -o $$out $(LIBS); \
	mv -f $$out $(GAME_SO)

.PHONY: app
app: $(APP)

.PHONY: run
run: all
	./$(APP)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(APP) $(GAME_SO) game_*.so


