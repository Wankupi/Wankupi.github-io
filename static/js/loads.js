let isLocal = (location.hostname == "localhost" || location.hostname == "127.0.0.1");
let isMainPage = (location.pathname == "/");

var MathJax = { startup: { typeset: (!isMainPage), output: 'chtml' }, tex: { inlineMath: [['$', '$'], ['\\(', '\\)']] }, options: { enableMenu: false } };

(function () {
  let d = document.createElement("script");
  d.id = "MathJax-script";
  d.src = (isLocal ? "/static/js/MathJax/es5/tex-chtml.js" : "https://cdn.jsdelivr.net/npm/mathjax/es5/tex-chtml.js");
  d.async = true;
  document.head.appendChild(d);
})();

if (isMainPage) {
  (function () {
    let d = document.createElement("script");
    d.id = "jquerj-script";
    d.src = (isLocal ? "/static/js/jquery/jquery.min.js" : "https://cdn.jsdelivr.net/npm/jquery@3.5.1/dist/jquery.min.js");
    d.addEventListener("load", (e) => {
      $(".scroll-down").on("click", function () { $("html,body").animate({ scrollTop: $("main").offset().top }, 1000); });
      $(".back-top").on("click", e => { $("html,body").animate({ scrollTop: 0 }, 1000); });
    });
    document.head.appendChild(d);
  })();
}
else {
  document.title += " | Wankupi";

  function addCSSfile(url) { let lnk = document.createElement("link"); lnk.rel = "stylesheet"; lnk.href = url; document.head.appendChild(lnk); }

  addCSSfile("/static/css/highlight.css");

  (function () {
    let d = document.createElement("script");
    d.src = "/static/js/highlight/highlight.pack.js";
    d.async = true;
    d.addEventListener("load", e => { hljs.initHighlighting(); });
    document.head.appendChild(d);
  })();

  (function () {
    function loadValine() {
      new Valine({
        el: '#Comment',
        app_id: '0fXMSbCD7SIxO3z7u5j1VjkL-gzGzoHsz',
        app_key: 'eIi8ECHYotfQqPB4AQRI6nfi',
        placeholder: '写下你的精彩评论！',
        lang: 'zh-CN',
        visitor: false,
        recordIP: true,
        requiredFields: ['nick']
      });
    }
    let d = document.createElement("script");
    d.src = "https://cdn.jsdelivr.net/npm/valine/dist/Valine.min.js";
    d.async = true;
    d.addEventListener("load", loadValine);
    document.head.appendChild(d);
  })();
}