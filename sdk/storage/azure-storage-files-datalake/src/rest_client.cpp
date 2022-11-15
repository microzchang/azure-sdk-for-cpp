
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// Code generated by Microsoft (R) AutoRest C++ Code Generator.
// Changes may cause incorrect behavior and will be lost if the code is regenerated.
#include <azure/storage/files/datalake/rest_client.hpp>

#include <cstdint>
#include <string>

#include <azure/core/base64.hpp>
#include <azure/core/context.hpp>
#include <azure/core/datetime.hpp>
#include <azure/core/etag.hpp>
#include <azure/core/http/http.hpp>
#include <azure/core/http/http_status_code.hpp>
#include <azure/core/internal/http/pipeline.hpp>
#include <azure/core/internal/json/json.hpp>
#include <azure/core/io/body_stream.hpp>
#include <azure/core/response.hpp>
#include <azure/core/url.hpp>
#include <azure/storage/common/crypt.hpp>
#include <azure/storage/common/storage_common.hpp>
#include <azure/storage/common/storage_exception.hpp>

namespace Azure { namespace Storage { namespace Files { namespace DataLake {
  namespace Models {
    namespace _detail {
      const PathRenameMode PathRenameMode::Legacy("legacy");
      const PathRenameMode PathRenameMode::Posix("posix");
      const PathSetAccessControlListRecursiveMode PathSetAccessControlListRecursiveMode::Set("set");
      const PathSetAccessControlListRecursiveMode PathSetAccessControlListRecursiveMode::Modify(
          "modify");
      const PathSetAccessControlListRecursiveMode PathSetAccessControlListRecursiveMode::Remove(
          "remove");
    } // namespace _detail
    const PublicAccessType PublicAccessType::None("");
    const PublicAccessType PublicAccessType::FileSystem("container");
    const PublicAccessType PublicAccessType::Path("blob");
    const PathResourceType PathResourceType::Directory("directory");
    const PathResourceType PathResourceType::File("file");
    const LeaseAction LeaseAction::Acquire("acquire");
    const LeaseAction LeaseAction::AutoRenew("auto-renew");
    const LeaseAction LeaseAction::Release("release");
    const LeaseAction LeaseAction::AcquireRelease("acquire-release");
  } // namespace Models
  namespace _detail {
    Response<Models::_detail::PathList> FileSystemClient::ListPaths(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const ListFileSystemPathsOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Get, url);
      request.GetUrl().AppendQueryParameter("resource", "filesystem");
      if (options.RequestId.HasValue() && !options.RequestId.Value().empty())
      {
        request.SetHeader("x-ms-client-request-id", options.RequestId.Value());
      }
      if (options.Timeout.HasValue())
      {
        request.GetUrl().AppendQueryParameter("timeout", std::to_string(options.Timeout.Value()));
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      if (options.ContinuationToken.HasValue() && !options.ContinuationToken.Value().empty())
      {
        request.GetUrl().AppendQueryParameter(
            "continuation", _internal::UrlEncodeQueryParameter(options.ContinuationToken.Value()));
      }
      if (options.Path.HasValue() && !options.Path.Value().empty())
      {
        request.GetUrl().AppendQueryParameter(
            "directory", _internal::UrlEncodeQueryParameter(options.Path.Value()));
      }
      request.GetUrl().AppendQueryParameter("recursive", options.Recursive ? "true" : "false");
      if (options.MaxResults.HasValue())
      {
        request.GetUrl().AppendQueryParameter(
            "maxResults", std::to_string(options.MaxResults.Value()));
      }
      if (options.Upn.HasValue())
      {
        request.GetUrl().AppendQueryParameter("upn", options.Upn.Value() ? "true" : "false");
      }
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Ok)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::_detail::PathList response;
      {
        const auto& responseBody = pRawResponse->GetBody();
        auto jsonRoot
            = Core::Json::_internal::json::parse(responseBody.begin(), responseBody.end());
        for (const auto& var0 : jsonRoot.count("paths") != 0 && jsonRoot["paths"].is_array()
                 ? jsonRoot["paths"]
                 : Core::Json::_internal::json::array())
        {
          Models::_detail::PathItem vectorElement2;
          vectorElement2.Name = var0["name"].get<std::string>();
          if (var0.count("isDirectory") != 0)
          {
            vectorElement2.IsDirectory = var0["isDirectory"].is_boolean()
                ? var0["isDirectory"].get<bool>()
                : var0["isDirectory"].get<std::string>() == std::string("true");
          }
          vectorElement2.LastModified = DateTime::Parse(
              var0["lastModified"].get<std::string>(), Azure::DateTime::DateFormat::Rfc1123);
          vectorElement2.FileSize = var0["contentLength"].is_number_integer()
              ? var0["contentLength"].get<int64_t>()
              : std::stoll(var0["contentLength"].get<std::string>());
          vectorElement2.Owner = var0["owner"].get<std::string>();
          vectorElement2.Group = var0["group"].get<std::string>();
          vectorElement2.Permissions = var0["permissions"].get<std::string>();
          if (var0.count("EncryptionScope") != 0)
          {
            vectorElement2.EncryptionScope = var0["EncryptionScope"].get<std::string>();
          }
          if (var0.count("creationTime") != 0)
          {
            vectorElement2.CreatedOn = var0["creationTime"].get<std::string>();
          }
          if (var0.count("expiryTime") != 0)
          {
            vectorElement2.ExpiresOn = var0["expiryTime"].get<std::string>();
          }
          if (var0.count("etag") != 0)
          {
            vectorElement2.ETag = var0["etag"].get<std::string>();
          }
          response.Paths.emplace_back(std::move(vectorElement2));
        }
      }
      if (pRawResponse->GetHeaders().count("x-ms-continuation") != 0)
      {
        response.ContinuationToken = pRawResponse->GetHeaders().at("x-ms-continuation");
      }
      return Response<Models::_detail::PathList>(std::move(response), std::move(pRawResponse));
    }
    Response<Models::CreatePathResult> PathClient::Create(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const CreatePathOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Put, url);
      if (options.RequestId.HasValue() && !options.RequestId.Value().empty())
      {
        request.SetHeader("x-ms-client-request-id", options.RequestId.Value());
      }
      if (options.Timeout.HasValue())
      {
        request.GetUrl().AppendQueryParameter("timeout", std::to_string(options.Timeout.Value()));
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      if (options.Resource.HasValue() && !options.Resource.Value().ToString().empty())
      {
        request.GetUrl().AppendQueryParameter(
            "resource", _internal::UrlEncodeQueryParameter(options.Resource.Value().ToString()));
      }
      if (options.ContinuationToken.HasValue() && !options.ContinuationToken.Value().empty())
      {
        request.GetUrl().AppendQueryParameter(
            "continuation", _internal::UrlEncodeQueryParameter(options.ContinuationToken.Value()));
      }
      if (options.Mode.HasValue() && !options.Mode.Value().empty())
      {
        request.GetUrl().AppendQueryParameter(
            "mode", _internal::UrlEncodeQueryParameter(options.Mode.Value()));
      }
      if (options.CacheControl.HasValue() && !options.CacheControl.Value().empty())
      {
        request.SetHeader("x-ms-cache-control", options.CacheControl.Value());
      }
      if (options.ContentEncoding.HasValue() && !options.ContentEncoding.Value().empty())
      {
        request.SetHeader("x-ms-content-encoding", options.ContentEncoding.Value());
      }
      if (options.ContentLanguage.HasValue() && !options.ContentLanguage.Value().empty())
      {
        request.SetHeader("x-ms-content-language", options.ContentLanguage.Value());
      }
      if (options.ContentDisposition.HasValue() && !options.ContentDisposition.Value().empty())
      {
        request.SetHeader("x-ms-content-disposition", options.ContentDisposition.Value());
      }
      if (options.ContentType.HasValue() && !options.ContentType.Value().empty())
      {
        request.SetHeader("x-ms-content-type", options.ContentType.Value());
      }
      if (options.RenameSource.HasValue() && !options.RenameSource.Value().empty())
      {
        request.SetHeader("x-ms-rename-source", options.RenameSource.Value());
      }
      if (options.LeaseId.HasValue() && !options.LeaseId.Value().empty())
      {
        request.SetHeader("x-ms-lease-id", options.LeaseId.Value());
      }
      if (options.SourceLeaseId.HasValue() && !options.SourceLeaseId.Value().empty())
      {
        request.SetHeader("x-ms-source-lease-id", options.SourceLeaseId.Value());
      }
      if (options.Properties.HasValue() && !options.Properties.Value().empty())
      {
        request.SetHeader("x-ms-properties", options.Properties.Value());
      }
      if (options.Permissions.HasValue() && !options.Permissions.Value().empty())
      {
        request.SetHeader("x-ms-permissions", options.Permissions.Value());
      }
      if (options.Umask.HasValue() && !options.Umask.Value().empty())
      {
        request.SetHeader("x-ms-umask", options.Umask.Value());
      }
      if (options.IfMatch.HasValue() && !options.IfMatch.ToString().empty())
      {
        request.SetHeader("If-Match", options.IfMatch.ToString());
      }
      if (options.IfNoneMatch.HasValue() && !options.IfNoneMatch.ToString().empty())
      {
        request.SetHeader("If-None-Match", options.IfNoneMatch.ToString());
      }
      if (options.IfModifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Modified-Since",
            options.IfModifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.IfUnmodifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Unmodified-Since",
            options.IfUnmodifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.SourceIfMatch.HasValue() && !options.SourceIfMatch.ToString().empty())
      {
        request.SetHeader("x-ms-source-if-match", options.SourceIfMatch.ToString());
      }
      if (options.SourceIfNoneMatch.HasValue() && !options.SourceIfNoneMatch.ToString().empty())
      {
        request.SetHeader("x-ms-source-if-none-match", options.SourceIfNoneMatch.ToString());
      }
      if (options.SourceIfModifiedSince.HasValue())
      {
        request.SetHeader(
            "x-ms-source-if-modified-since",
            options.SourceIfModifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.SourceIfUnmodifiedSince.HasValue())
      {
        request.SetHeader(
            "x-ms-source-if-unmodified-since",
            options.SourceIfUnmodifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.EncryptionKey.HasValue() && !options.EncryptionKey.Value().empty())
      {
        request.SetHeader("x-ms-encryption-key", options.EncryptionKey.Value());
      }
      if (options.EncryptionKeySha256.HasValue()
          && !Core::Convert::Base64Encode(options.EncryptionKeySha256.Value()).empty())
      {
        request.SetHeader(
            "x-ms-encryption-key-sha256",
            Core::Convert::Base64Encode(options.EncryptionKeySha256.Value()));
      }
      if (options.EncryptionAlgorithm.HasValue() && !options.EncryptionAlgorithm.Value().empty())
      {
        request.SetHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.Value());
      }
      if (options.Owner.HasValue() && !options.Owner.Value().empty())
      {
        request.SetHeader("x-ms-owner", options.Owner.Value());
      }
      if (options.Group.HasValue() && !options.Group.Value().empty())
      {
        request.SetHeader("x-ms-group", options.Group.Value());
      }
      if (options.Acl.HasValue() && !options.Acl.Value().empty())
      {
        request.SetHeader("x-ms-acl", options.Acl.Value());
      }
      if (options.ProposedLeaseId.HasValue() && !options.ProposedLeaseId.Value().empty())
      {
        request.SetHeader("x-ms-proposed-lease-id", options.ProposedLeaseId.Value());
      }
      if (options.LeaseDuration.HasValue())
      {
        request.SetHeader("x-ms-lease-duration", std::to_string(options.LeaseDuration.Value()));
      }
      if (options.ExpiryOptions.HasValue() && !options.ExpiryOptions.Value().empty())
      {
        request.SetHeader("x-ms-expiry-option", options.ExpiryOptions.Value());
      }
      if (options.ExpiresOn.HasValue() && !options.ExpiresOn.Value().empty())
      {
        request.SetHeader("x-ms-expiry-time", options.ExpiresOn.Value());
      }
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Created)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::CreatePathResult response;
      response.ETag = ETag(pRawResponse->GetHeaders().at("ETag"));
      response.LastModified = DateTime::Parse(
          pRawResponse->GetHeaders().at("Last-Modified"), Azure::DateTime::DateFormat::Rfc1123);
      if (pRawResponse->GetHeaders().count("Content-Length") != 0)
      {
        response.FileSize = std::stoll(pRawResponse->GetHeaders().at("Content-Length"));
      }
      if (pRawResponse->GetHeaders().count("x-ms-request-server-encrypted") != 0)
      {
        response.IsServerEncrypted
            = pRawResponse->GetHeaders().at("x-ms-request-server-encrypted") == std::string("true");
      }
      if (pRawResponse->GetHeaders().count("x-ms-encryption-key-sha256") != 0)
      {
        response.EncryptionKeySha256 = Core::Convert::Base64Decode(
            pRawResponse->GetHeaders().at("x-ms-encryption-key-sha256"));
      }
      return Response<Models::CreatePathResult>(std::move(response), std::move(pRawResponse));
    }
    Response<Models::DeletePathResult> PathClient::Delete(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const DeletePathOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Delete, url);
      if (options.RequestId.HasValue() && !options.RequestId.Value().empty())
      {
        request.SetHeader("x-ms-client-request-id", options.RequestId.Value());
      }
      if (options.Timeout.HasValue())
      {
        request.GetUrl().AppendQueryParameter("timeout", std::to_string(options.Timeout.Value()));
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      if (options.Recursive.HasValue())
      {
        request.GetUrl().AppendQueryParameter(
            "recursive", options.Recursive.Value() ? "true" : "false");
      }
      if (options.ContinuationToken.HasValue() && !options.ContinuationToken.Value().empty())
      {
        request.GetUrl().AppendQueryParameter(
            "continuation", _internal::UrlEncodeQueryParameter(options.ContinuationToken.Value()));
      }
      if (options.LeaseId.HasValue() && !options.LeaseId.Value().empty())
      {
        request.SetHeader("x-ms-lease-id", options.LeaseId.Value());
      }
      if (options.IfMatch.HasValue() && !options.IfMatch.ToString().empty())
      {
        request.SetHeader("If-Match", options.IfMatch.ToString());
      }
      if (options.IfNoneMatch.HasValue() && !options.IfNoneMatch.ToString().empty())
      {
        request.SetHeader("If-None-Match", options.IfNoneMatch.ToString());
      }
      if (options.IfModifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Modified-Since",
            options.IfModifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.IfUnmodifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Unmodified-Since",
            options.IfUnmodifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Ok)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::DeletePathResult response;
      return Response<Models::DeletePathResult>(std::move(response), std::move(pRawResponse));
    }
    Response<Models::SetPathAccessControlListResult> PathClient::SetAccessControlList(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const SetPathAccessControlListOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Patch, url);
      request.GetUrl().AppendQueryParameter("action", "setAccessControl");
      if (options.LeaseId.HasValue() && !options.LeaseId.Value().empty())
      {
        request.SetHeader("x-ms-lease-id", options.LeaseId.Value());
      }
      if (options.Owner.HasValue() && !options.Owner.Value().empty())
      {
        request.SetHeader("x-ms-owner", options.Owner.Value());
      }
      if (options.Group.HasValue() && !options.Group.Value().empty())
      {
        request.SetHeader("x-ms-group", options.Group.Value());
      }
      if (options.Permissions.HasValue() && !options.Permissions.Value().empty())
      {
        request.SetHeader("x-ms-permissions", options.Permissions.Value());
      }
      if (options.Acl.HasValue() && !options.Acl.Value().empty())
      {
        request.SetHeader("x-ms-acl", options.Acl.Value());
      }
      if (options.IfMatch.HasValue() && !options.IfMatch.ToString().empty())
      {
        request.SetHeader("If-Match", options.IfMatch.ToString());
      }
      if (options.IfNoneMatch.HasValue() && !options.IfNoneMatch.ToString().empty())
      {
        request.SetHeader("If-None-Match", options.IfNoneMatch.ToString());
      }
      if (options.IfModifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Modified-Since",
            options.IfModifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.IfUnmodifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Unmodified-Since",
            options.IfUnmodifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Ok)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::SetPathAccessControlListResult response;
      response.ETag = ETag(pRawResponse->GetHeaders().at("ETag"));
      response.LastModified = DateTime::Parse(
          pRawResponse->GetHeaders().at("Last-Modified"), Azure::DateTime::DateFormat::Rfc1123);
      return Response<Models::SetPathAccessControlListResult>(
          std::move(response), std::move(pRawResponse));
    }
    Response<Models::_detail::SetAccessControlListRecursiveResult>
    PathClient::SetAccessControlListRecursive(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const SetPathAccessControlListRecursiveOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Patch, url);
      request.GetUrl().AppendQueryParameter("action", "setAccessControlRecursive");
      if (options.ContinuationToken.HasValue() && !options.ContinuationToken.Value().empty())
      {
        request.GetUrl().AppendQueryParameter(
            "continuation", _internal::UrlEncodeQueryParameter(options.ContinuationToken.Value()));
      }
      if (!options.Mode.empty())
      {
        request.GetUrl().AppendQueryParameter(
            "mode", _internal::UrlEncodeQueryParameter(options.Mode));
      }
      if (options.ForceFlag.HasValue())
      {
        request.GetUrl().AppendQueryParameter(
            "forceFlag", options.ForceFlag.Value() ? "true" : "false");
      }
      if (options.MaxRecords.HasValue())
      {
        request.GetUrl().AppendQueryParameter(
            "maxRecords", std::to_string(options.MaxRecords.Value()));
      }
      if (options.Acl.HasValue() && !options.Acl.Value().empty())
      {
        request.SetHeader("x-ms-acl", options.Acl.Value());
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Ok)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::_detail::SetAccessControlListRecursiveResult response;
      {
        const auto& responseBody = pRawResponse->GetBody();
        auto jsonRoot
            = Core::Json::_internal::json::parse(responseBody.begin(), responseBody.end());
        response.NumberOfSuccessfulDirectories
            = jsonRoot["directoriesSuccessful"].is_number_integer()
            ? jsonRoot["directoriesSuccessful"].get<int32_t>()
            : std::stoi(jsonRoot["directoriesSuccessful"].get<std::string>());
        response.NumberOfSuccessfulFiles = jsonRoot["filesSuccessful"].is_number_integer()
            ? jsonRoot["filesSuccessful"].get<int32_t>()
            : std::stoi(jsonRoot["filesSuccessful"].get<std::string>());
        response.NumberOfFailures = jsonRoot["failureCount"].is_number_integer()
            ? jsonRoot["failureCount"].get<int32_t>()
            : std::stoi(jsonRoot["failureCount"].get<std::string>());
        for (const auto& var0 :
             jsonRoot.count("failedEntries") != 0 && jsonRoot["failedEntries"].is_array()
                 ? jsonRoot["failedEntries"]
                 : Core::Json::_internal::json::array())
        {
          Models::AclFailedEntry vectorElement2;
          vectorElement2.Name = var0["name"].get<std::string>();
          vectorElement2.Type = var0["type"].get<std::string>();
          vectorElement2.ErrorMessage = var0["errorMessage"].get<std::string>();
          response.FailedEntries.emplace_back(std::move(vectorElement2));
        }
      }
      if (pRawResponse->GetHeaders().count("x-ms-continuation") != 0)
      {
        response.ContinuationToken = pRawResponse->GetHeaders().at("x-ms-continuation");
      }
      return Response<Models::_detail::SetAccessControlListRecursiveResult>(
          std::move(response), std::move(pRawResponse));
    }
    Response<Models::_detail::UndeletePathResult> PathClient::Undelete(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const UndeletePathOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Put, url);
      request.GetUrl().AppendQueryParameter("comp", "undelete");
      if (options.UndeleteSource.HasValue() && !options.UndeleteSource.Value().empty())
      {
        request.SetHeader("x-ms-undelete-source", options.UndeleteSource.Value());
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Ok)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::_detail::UndeletePathResult response;
      if (pRawResponse->GetHeaders().count("x-ms-resource-type") != 0)
      {
        response.ResourceType = pRawResponse->GetHeaders().at("x-ms-resource-type");
      }
      return Response<Models::_detail::UndeletePathResult>(
          std::move(response), std::move(pRawResponse));
    }
    Response<Models::_detail::GetPathAccessControlListResult> PathClient::GetAccessControlList(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const GetPathAccessControlListOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Head, url);
      request.GetUrl().AppendQueryParameter("action", "getAccessControl");
      if (options.Upn.HasValue())
      {
        request.GetUrl().AppendQueryParameter("upn", options.Upn.Value() ? "true" : "false");
      }
      if (options.LeaseId.HasValue() && !options.LeaseId.Value().empty())
      {
        request.SetHeader("x-ms-lease-id", options.LeaseId.Value());
      }
      if (options.IfMatch.HasValue() && !options.IfMatch.ToString().empty())
      {
        request.SetHeader("If-Match", options.IfMatch.ToString());
      }
      if (options.IfNoneMatch.HasValue() && !options.IfNoneMatch.ToString().empty())
      {
        request.SetHeader("If-None-Match", options.IfNoneMatch.ToString());
      }
      if (options.IfModifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Modified-Since",
            options.IfModifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.IfUnmodifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Unmodified-Since",
            options.IfUnmodifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Ok)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::_detail::GetPathAccessControlListResult response;
      response.Owner = pRawResponse->GetHeaders().at("x-ms-owner");
      response.Group = pRawResponse->GetHeaders().at("x-ms-group");
      response.Permissions = pRawResponse->GetHeaders().at("x-ms-permissions");
      response.Acl = pRawResponse->GetHeaders().at("x-ms-acl");
      return Response<Models::_detail::GetPathAccessControlListResult>(
          std::move(response), std::move(pRawResponse));
    }
    Response<Models::FlushFileResult> FileClient::Flush(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        const FlushFileOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Patch, url);
      request.GetUrl().AppendQueryParameter("action", "flush");
      if (options.Position.HasValue())
      {
        request.GetUrl().AppendQueryParameter("position", std::to_string(options.Position.Value()));
      }
      if (options.RetainUncommittedData.HasValue())
      {
        request.GetUrl().AppendQueryParameter(
            "retainUncommittedData", options.RetainUncommittedData.Value() ? "true" : "false");
      }
      if (options.Close.HasValue())
      {
        request.GetUrl().AppendQueryParameter("close", options.Close.Value() ? "true" : "false");
      }
      request.SetHeader("Content-Length", "0");
      if (options.ContentMD5.HasValue()
          && !Core::Convert::Base64Encode(options.ContentMD5.Value()).empty())
      {
        request.SetHeader(
            "x-ms-content-md5", Core::Convert::Base64Encode(options.ContentMD5.Value()));
      }
      if (options.LeaseId.HasValue() && !options.LeaseId.Value().empty())
      {
        request.SetHeader("x-ms-lease-id", options.LeaseId.Value());
      }
      if (options.LeaseAction.HasValue() && !options.LeaseAction.Value().ToString().empty())
      {
        request.SetHeader("x-ms-lease-action", options.LeaseAction.Value().ToString());
      }
      if (options.LeaseDuration.HasValue())
      {
        request.SetHeader("x-ms-lease-duration", std::to_string(options.LeaseDuration.Value()));
      }
      if (options.ProposedLeaseId.HasValue() && !options.ProposedLeaseId.Value().empty())
      {
        request.SetHeader("x-ms-proposed-lease-id", options.ProposedLeaseId.Value());
      }
      if (options.CacheControl.HasValue() && !options.CacheControl.Value().empty())
      {
        request.SetHeader("x-ms-cache-control", options.CacheControl.Value());
      }
      if (options.ContentType.HasValue() && !options.ContentType.Value().empty())
      {
        request.SetHeader("x-ms-content-type", options.ContentType.Value());
      }
      if (options.ContentDisposition.HasValue() && !options.ContentDisposition.Value().empty())
      {
        request.SetHeader("x-ms-content-disposition", options.ContentDisposition.Value());
      }
      if (options.ContentEncoding.HasValue() && !options.ContentEncoding.Value().empty())
      {
        request.SetHeader("x-ms-content-encoding", options.ContentEncoding.Value());
      }
      if (options.ContentLanguage.HasValue() && !options.ContentLanguage.Value().empty())
      {
        request.SetHeader("x-ms-content-language", options.ContentLanguage.Value());
      }
      if (options.IfMatch.HasValue() && !options.IfMatch.ToString().empty())
      {
        request.SetHeader("If-Match", options.IfMatch.ToString());
      }
      if (options.IfNoneMatch.HasValue() && !options.IfNoneMatch.ToString().empty())
      {
        request.SetHeader("If-None-Match", options.IfNoneMatch.ToString());
      }
      if (options.IfModifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Modified-Since",
            options.IfModifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      if (options.IfUnmodifiedSince.HasValue())
      {
        request.SetHeader(
            "If-Unmodified-Since",
            options.IfUnmodifiedSince.Value().ToString(Azure::DateTime::DateFormat::Rfc1123));
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      if (options.EncryptionKey.HasValue() && !options.EncryptionKey.Value().empty())
      {
        request.SetHeader("x-ms-encryption-key", options.EncryptionKey.Value());
      }
      if (options.EncryptionKeySha256.HasValue()
          && !Core::Convert::Base64Encode(options.EncryptionKeySha256.Value()).empty())
      {
        request.SetHeader(
            "x-ms-encryption-key-sha256",
            Core::Convert::Base64Encode(options.EncryptionKeySha256.Value()));
      }
      if (options.EncryptionAlgorithm.HasValue() && !options.EncryptionAlgorithm.Value().empty())
      {
        request.SetHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.Value());
      }
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Ok)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::FlushFileResult response;
      response.ETag = ETag(pRawResponse->GetHeaders().at("ETag"));
      response.LastModified = DateTime::Parse(
          pRawResponse->GetHeaders().at("Last-Modified"), Azure::DateTime::DateFormat::Rfc1123);
      response.FileSize = std::stoll(pRawResponse->GetHeaders().at("Content-Length"));
      response.IsServerEncrypted
          = pRawResponse->GetHeaders().at("x-ms-request-server-encrypted") == std::string("true");
      if (pRawResponse->GetHeaders().count("x-ms-encryption-key-sha256") != 0)
      {
        response.EncryptionKeySha256 = Core::Convert::Base64Decode(
            pRawResponse->GetHeaders().at("x-ms-encryption-key-sha256"));
      }
      if (pRawResponse->GetHeaders().count("x-ms-lease-renewed") != 0)
      {
        response.LeaseRenewed
            = pRawResponse->GetHeaders().at("x-ms-lease-renewed") == std::string("true");
      }
      return Response<Models::FlushFileResult>(std::move(response), std::move(pRawResponse));
    }
    Response<Models::AppendFileResult> FileClient::Append(
        Core::Http::_internal::HttpPipeline& pipeline,
        const Core::Url& url,
        Core::IO::BodyStream& requestBody,
        const AppendFileOptions& options,
        const Core::Context& context)
    {
      auto request = Core::Http::Request(Core::Http::HttpMethod::Patch, url, &requestBody);
      request.GetUrl().AppendQueryParameter("action", "append");
      if (options.Position.HasValue())
      {
        request.GetUrl().AppendQueryParameter("position", std::to_string(options.Position.Value()));
      }
      request.SetHeader("Content-Length", std::to_string(requestBody.Length()));
      if (options.TransactionalContentHash.HasValue()
          && !Core::Convert::Base64Encode(options.TransactionalContentHash.Value()).empty())
      {
        request.SetHeader(
            "Content-MD5", Core::Convert::Base64Encode(options.TransactionalContentHash.Value()));
      }
      if (options.TransactionalContentCrc64.HasValue()
          && !Core::Convert::Base64Encode(options.TransactionalContentCrc64.Value()).empty())
      {
        request.SetHeader(
            "x-ms-content-crc64",
            Core::Convert::Base64Encode(options.TransactionalContentCrc64.Value()));
      }
      if (options.LeaseId.HasValue() && !options.LeaseId.Value().empty())
      {
        request.SetHeader("x-ms-lease-id", options.LeaseId.Value());
      }
      if (options.LeaseAction.HasValue() && !options.LeaseAction.Value().ToString().empty())
      {
        request.SetHeader("x-ms-lease-action", options.LeaseAction.Value().ToString());
      }
      if (options.LeaseDuration.HasValue())
      {
        request.SetHeader("x-ms-lease-duration", std::to_string(options.LeaseDuration.Value()));
      }
      if (options.ProposedLeaseId.HasValue() && !options.ProposedLeaseId.Value().empty())
      {
        request.SetHeader("x-ms-proposed-lease-id", options.ProposedLeaseId.Value());
      }
      request.SetHeader("x-ms-version", "2021-06-08");
      if (options.EncryptionKey.HasValue() && !options.EncryptionKey.Value().empty())
      {
        request.SetHeader("x-ms-encryption-key", options.EncryptionKey.Value());
      }
      if (options.EncryptionKeySha256.HasValue()
          && !Core::Convert::Base64Encode(options.EncryptionKeySha256.Value()).empty())
      {
        request.SetHeader(
            "x-ms-encryption-key-sha256",
            Core::Convert::Base64Encode(options.EncryptionKeySha256.Value()));
      }
      if (options.EncryptionAlgorithm.HasValue() && !options.EncryptionAlgorithm.Value().empty())
      {
        request.SetHeader("x-ms-encryption-algorithm", options.EncryptionAlgorithm.Value());
      }
      if (options.Flush.HasValue())
      {
        request.GetUrl().AppendQueryParameter("flush", options.Flush.Value() ? "true" : "false");
      }
      auto pRawResponse = pipeline.Send(request, context);
      auto httpStatusCode = pRawResponse->GetStatusCode();
      if (httpStatusCode != Core::Http::HttpStatusCode::Accepted)
      {
        throw StorageException::CreateFromResponse(std::move(pRawResponse));
      }
      Models::AppendFileResult response;
      if (pRawResponse->GetHeaders().count("Content-MD5") != 0)
      {
        response.TransactionalContentHash = ContentHash();
        response.TransactionalContentHash.Value().Value
            = Core::Convert::Base64Decode(pRawResponse->GetHeaders().at("Content-MD5"));
        response.TransactionalContentHash.Value().Algorithm = HashAlgorithm::Md5;
      }
      if (pRawResponse->GetHeaders().count("x-ms-content-crc64") != 0)
      {
        response.TransactionalContentHash = ContentHash();
        response.TransactionalContentHash.Value().Value
            = Core::Convert::Base64Decode(pRawResponse->GetHeaders().at("x-ms-content-crc64"));
        response.TransactionalContentHash.Value().Algorithm = HashAlgorithm::Crc64;
      }
      response.IsServerEncrypted
          = pRawResponse->GetHeaders().at("x-ms-request-server-encrypted") == std::string("true");
      if (pRawResponse->GetHeaders().count("x-ms-encryption-key-sha256") != 0)
      {
        response.EncryptionKeySha256 = Core::Convert::Base64Decode(
            pRawResponse->GetHeaders().at("x-ms-encryption-key-sha256"));
      }
      if (pRawResponse->GetHeaders().count("x-ms-lease-renewed") != 0)
      {
        response.LeaseRenewed
            = pRawResponse->GetHeaders().at("x-ms-lease-renewed") == std::string("true");
      }
      return Response<Models::AppendFileResult>(std::move(response), std::move(pRawResponse));
    }
  } // namespace _detail
}}}} // namespace Azure::Storage::Files::DataLake