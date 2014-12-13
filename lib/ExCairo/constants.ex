defmodule ExCairo.Constants do
  defmodule Format do
    @moduledoc """
    *corresponds*: `typedef enum cairo_format_t`

    Identifies the memory format of the image data
    """
    def invalid,    do: -1
    def argb32,     do: 0
    def rgb24,      do: 1
    def a8,         do: 2
    def a1,         do: 3
    def rgb16_565,  do: 4
    def rgb30,      do: 5
  end

  defmodule Font do
    defmodule Slant do
      @moduledoc """
      *corresponds*: `typedef enum cairo_font_slant_t`

      Font slant (normal, italic, oblique)
      """
      def normal,   do: 0
      def italic,   do: 1
      def oblique,  do: 2
    end

    defmodule Weight do
      @moduledoc """
      *corresponds*: `typedef enum cairo_font_weight_t`

      Font weight (normal, bold)
      """
      def normal,   do: 0
      def bold,     do: 1
    end
  end
end
