$(document).ready(function () {
    $('#tab1').show();

    $('.tab-navigation a').click(function () {
        var tabId = $(this).attr('href');

        $('.tab-content').hide();

        $(tabId).show();

        $('.tab-navigation a').removeClass('active');

        $(this).addClass('active');

        $('a.active').addClass()

        return false;
    });
});