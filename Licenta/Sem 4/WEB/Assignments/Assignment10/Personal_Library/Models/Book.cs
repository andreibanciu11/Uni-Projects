using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Personal_Library.Models
{
    public class Book
    {
        private string author;
        private string title;
        private int number_of_pages;
        private string genre;

        public string Author { get => author; set => author = value; }
        public string Title { get => title; set => title = value; }
        public string Genre { get => genre; set => genre = value; }
        public int NumberOfPages { get => number_of_pages; set => number_of_pages = value;}
    }
}