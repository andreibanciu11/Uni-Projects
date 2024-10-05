using Personal_Library.DataAbstractionLayer;
using Personal_Library.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Personal_Library.Controllers
{
    public class AddBookController : Controller
    {
        private DAL dal = new DAL();

        public ActionResult Index()
        {
            return View("ViewAddBook");
        }

        [HttpPost]
        public ActionResult AddBook(string author, string title, string number_of_pages, string genre)
        {
            int numberOfPages;
            int.TryParse(number_of_pages, out numberOfPages);

            Book book = new Book { Title = title, Author = author, NumberOfPages = numberOfPages, Genre = genre };
            string username = HttpContext.Session["user"].ToString();
            dal.AddBook(book, username);

            return Redirect("/Main");
        }
    }
}