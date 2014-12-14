defmodule ExCairo do
  @on_load {:init, 0}

  @moduledoc """
  A nif that provides a native interface
  to to Cairo 2D graphics library
  """
  def init do
    # Get the name from the configuration file
    cfg = Application.get_all_env(:nif)
    lib_path = :filename.join(:code.priv_dir(:excairo), cfg[:name])

    # Assert success
    :ok = :erlang.load_nif(lib_path, 0)
  end

  @doc """
  Adds a circular arc of the given radius to the current path. 
  The arc is centered at (xc, yc), begins at angle1 and proceeds 
  in the direction of increasing angles to end at angle2. 
  
  If angle2 is less than angle1 it will be progressively increased 
  by 2*M_PI until it is greater than angle1.
  """
  def arc(_context, _xc, _yc, _radius, _angle1, _angle2) do
    exit :library_not_loaded
  end

  @doc """
  See `ExCairo.arc` for more details. This function differs only in the 
  direction of the arc between the two angles.
  """
  def arc_negative(_context, _xc, _yc, _radius, _angle1, _angle2) do
    exit :library_not_loaded  
  end

  @doc """
  Establishes a new clip region by intersecting the current clip region 
  with the current path as it would be filled by `ExCairo.fill` and according 
  to the current fill rule.
  """
  def clip(_context) do
    exit :library_not_loaded
  end

  @doc """
  Computes a bounding box in user coordinates covering the area 
  inside the current clip.
  """
  def clip_extents(_context, _x1, _y1, _x2, _y2) do
    exit :library_not_loaded
  end

  @doc """
  Unlike `ExCairo.clip`, `ExCairo.clip_preserve` preserves the path 
  within the cairo context.
  """
  def clip_preserve(_context) do
    exit :library_not_loaded
  end

  @doc """
  Adds a line segment to the path from the current point to the 
  beginning of the current sub-path, (the most recent point passed 
  `ExCairo.move_to`), and closes this sub-path. After this call the 
  current point will be at the joined endpoint of the sub-path. 
  """
  def close_path(_context) do
    exit :library_not_loaded
  end

  @doc """
  Gets the current clip region as a list of rectangles in user coordinates.
  Returns an empty list of the number of rectangles is zero.
  """
  def copy_clip_rectangle_list(_context) do
    exit :library_not_loaded
  end

  @doc """
  Creates a bitmap in memory

    iex> import ExCairo.Constants.Format
    iex> {:ok, surface} = ExCairo.image_surface_create(argb32, 16, 16)
    iex> is_binary(surface)
    true
  """
  def image_surface_create(_format, _width, _height) do
    exit :library_not_loaded
  end

  @doc """
  Creates a new cairo context given a surface bitmap

    iex> import ExCairo.Constants.Format
    iex> {:ok, surface} = ExCairo.image_surface_create(argb32, 16, 16)
    iex> {:ok, context} = ExCairo.create(surface)
    iex> is_binary(context)
    true
  """
  def create(_surface) do
    exit :library_not_loaded
  end

  @doc """
  Write a surface bitmap to a png file. This function
  accepts elixir strings

    iex> import ExCairo.Constants.Format
    iex> {:ok, surface} = ExCairo.image_surface_create(argb32, 16, 16)
    iex> ExCairo.surface_write_to_png(surface, "__temp__.png")
    iex> assert(File.exists? "__temp__.png")
    iex> File.rm("__temp__.png")
    :ok
  """
  def surface_write_to_png(_surface, _file) when is_list(_file) do
    exit :library_not_loaded
  end

  @doc """
  Select a font by specifying it's properties

    iex> import ExCairo.Constants.Format
    iex> alias ExCairo.Constants.Font.Slant
    iex> alias ExCairo.Constants.Font.Weight
    iex> {:ok, surface} = ExCairo.image_surface_create(argb32, 16, 16)
    iex> {:ok, context} = ExCairo.create(surface)
    iex> ExCairo.select_font_face(context, "serif", Slant.normal, Weight.normal)
    :ok
  """
  def select_font_face(_context, _family, _slant, _weight) do
    exit :library_not_loaded
  end

  @doc """
  Set the size of the currently selected font

    iex> import ExCairo.Constants.Format
    iex> {:ok, surface} = ExCairo.image_surface_create(argb32, 16, 16)
    iex> {:ok, context} = ExCairo.create(surface)
    iex> ExCairo.set_font_size(context, 32.0)
    :ok
  """
  def set_font_size(_context, _size) do
    exit :library_not_loaded
  end

  @doc """
  Sets the source pattern within cr to an opaque color. 
  This opaque color will then be used for any subsequent 
  drawing operation until a new source pattern is set

    iex> import ExCairo.Constants.Format
    iex> {:ok, surface} = ExCairo.image_surface_create(argb32, 16, 16)
    iex> {:ok, context} = ExCairo.create(surface)
    iex> ExCairo.set_source_rgb(context, 0.0, 0.0, 1.0)
    :ok
  """
  def set_source_rgb(_context, _red, _green, _blue) do
    exit :library_not_loaded
  end

  @doc """
  Begin a new sub-path. After this call the current point will be (x, y)

    iex> import ExCairo.Constants.Format
    iex> {:ok, surface} = ExCairo.image_surface_create(argb32, 16, 16)
    iex> {:ok, context} = ExCairo.create(surface)
    iex> ExCairo.move_to(context, 0, 0)
    :ok
  """
  def move_to(_context, _x, _y) do
    exit :library_not_loaded
  end

  @doc """
   Adds a line to the path from the current point to position (x, y) 
   in user-space coordinates. After this call the current point will be (x, y). 
  """
  def line_to(_context, _x, _y) do
    exit :library_not_loaded
  end

  @doc """
  A drawing operator that generates the shape from a string of UTF-8 characters, 
  rendered according to the current font_face, font_size (font_matrix), 
  and font_options.
  """
  def show_text(_context, _text) do
    exit :library_not_loaded
  end

  @doc """
  A drawing operator that strokes the current path according to the current 
  line width, line join, line cap, and dash settings
  """
  def stroke(_context) do
    exit :library_not_loaded
  end
end
