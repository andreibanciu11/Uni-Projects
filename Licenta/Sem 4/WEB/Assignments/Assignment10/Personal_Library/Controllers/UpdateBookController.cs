using Personal_Library.DataAbstractionLayer;
using Personal_Library.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Personal_Library.Controllers
{
    public class UpdateBookController : Controller
    {
        private DAL dal = new DAL();

        public ActionResult Index()
        {
            return View("ViewUpdateBook");
        }

        [HttpPost]
        public ActionResult UpdateBook(string author, string title, string number_of_pages, string genre)
        {
            int numberOfPages;
            int.TryParse(number_of_pages, out numberOfPages);

            string username = HttpContext.Session["user"].ToString();
            dal.UpdateBook(author, title, numberOfPages, genre, username);

            return Redirect("/Main");
        }
    }
}